#include "parse.h"

bitarray parseString(char *str, invertedIndex *index)
{
    TStack *terms, *operators;
    char *temp, *tok, *word;
    size_t noTerm = 0, wordLen;

    temp = strdup(str);
    terms = allocStack(MAX_TERMS);
    operators = allocStack(MAX_OP);
    /* CHECK MEM */
    for(tok = strtok(temp, " \n"); tok; tok = strtok(NULL, " \n")) {
        if(strcmp(tok, "&&") == 0 || strcmp(tok, "||") == 0) {
            addOperator(index, operators, terms, tok[0]);
        }
        else {
            word = strdup(tok);
            /* CHECK MEM */
            push(terms, (char) noTerm);
            wordLen = strlen(word);
            while(strcasecmp(word, index->terms[noTerm]) != 0 && wordLen != 0) {
                switch(word[0]) {
                    case '!':
                        addOperator(index, operators, terms, '!');
                        break;
                    case '(':
                        push(operators, '(');
                        break;
                    case ')':
                        closeParant(index, operators, terms);
                        wordLen = 0;
                        break;
                }
                if(wordLen > 0) {
                    strncpy(word, word + 1, wordLen--);
                }
            }
            free(word);
            noTerm++;
        }
        /*printf("DEBUG: BITARRAYS\n");
        for(size_t i = 0; i < index->noTerms; i++) {
            printf("DEBUG: BITARRAY[%lu]: ", i);
            printBitarray(index->found[i], index->noFiles);
            printf("\n");
        }
        printf("DEBUG: TERMS\n");
        printTerm(terms);
        printf("\n");
        printf("DEBUG: OP\n");
        printOp(operators);
        printf("\n\n");*/
    }
    finishOperations(index, operators, terms);

    freeStack(terms);
    freeStack(operators);
    free(temp);
    return index->found[0];
}

void addOperator(invertedIndex *index, TStack *operators, TStack *terms, char newOp)
{
    size_t first, second;
    char op;

    op = top(operators);
    while(op <= newOp && op != '(' && operators->currSz > 0) {
        if(op == '!') {
            first = (size_t) top(terms);
            FLIP_BITS(index->found[first], index->noFiles);
        }
        else {
            first = (size_t) pop(terms);
            second = (size_t) top(terms);
            if(op == '&') {
                for(size_t i = 0; i < index->noFiles; i++) {
                    index->tfidf[second][i] += MAX(index->tfidf[first][i], 0);
                }
                AND_BITARR(index->found[second], index->found[first], index->noFiles);
            }
            else if(op == '|') {
                for(size_t i = 0; i < index->noFiles; i++) {
                    index->tfidf[second][i] = MAX(index->tfidf[second][i],
                                              index->tfidf[first][i]);
                }
                OR_BITARR(index->found[second], index->found[first], index->noFiles);
            }
        }
        pop(operators);
        op = top(operators);
    }
    push(operators, newOp);
}

void closeParant(invertedIndex *index, TStack *operators, TStack *terms)
{
    size_t first, second;
    char op;

    op = top(operators);
    while(op != '(' && operators->currSz > 0) {
        if(op == '!') {
            first = (size_t) top(terms);
            for(size_t i = 0; i < index->noFiles; i++) {
                index->tfidf[first][i] = -index->tfidf[first][i];
            }
            FLIP_BITS(index->found[first], index->noFiles);
        }
        else {
            first = (size_t) pop(terms);
            second = (size_t) top(terms);
            if(op == '&') {
                for(size_t i = 0; i < index->noFiles; i++) {
                    index->tfidf[second][i] += MAX(index->tfidf[first][i], 0);
                }
                AND_BITARR(index->found[second], index->found[first], index->noFiles);
            }
            else if(op == '|') {
                for(size_t i = 0; i < index->noFiles; i++) {
                    index->tfidf[second][i] = MAX(index->tfidf[second][i],
                                              index->tfidf[first][i]);
                }
                OR_BITARR(index->found[second], index->found[first], index->noFiles);
            }
        }
        pop(operators);
        op = top(operators);
    }
    pop(operators);
}

void finishOperations(invertedIndex *index, TStack *operators, TStack *terms)
{
    size_t first, second;
    char op;

    op = top(operators);
    while(operators->currSz > 0) {
        if(op == '!') {
            first = (size_t) top(terms);
            for(size_t i = 0; i < index->noFiles; i++) {
                index->tfidf[first][i] = -index->tfidf[first][i];
            }
            FLIP_BITS(index->found[first], index->noFiles);
        }
        else {
            first = (size_t) pop(terms);
            second = (size_t) top(terms);
            if(op == '&') {
                for(size_t i = 0; i < index->noFiles; i++) {
                    index->tfidf[second][i] += MAX(index->tfidf[first][i], 0);
                }
                AND_BITARR(index->found[second], index->found[first], index->noFiles);
            }
            else if(op == '|') {
                for(size_t i = 0; i < index->noFiles; i++) {
                    index->tfidf[second][i] = MAX(index->tfidf[second][i],
                                              index->tfidf[first][i]);
                }
                OR_BITARR(index->found[second], index->found[first], index->noFiles);
            }
        }
        pop(operators);
        op = top(operators);
    }
}
