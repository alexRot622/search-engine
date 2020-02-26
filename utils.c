#include <stdio.h>
#include "utils.h"

int resultComp(const void *a, const void *b)
{
    if(((TResult *) a)->score < ((TResult *) b)->score) {
        return 1;
    }
    else if (((TResult *) a)->score == ((TResult *) b)->score) {
        return 0;
    }
    else {
        return -1;
    }
}

void showResults(invertedIndex *index)
{
    TResult *results;
    size_t noFound = 0;

    for(size_t i = 0; i < index->noFiles; i++) {
        if(GET_BIT(index->found[0], i)) {
            noFound++;    
        }
    }
    printf("%lu results found", noFound);
    if(noFound == 0) {
        printf(".\n");
    }
    else {
        printf(":\n");
    }
    results = (TResult *) malloc(noFound * sizeof(TResult));
    for(size_t i = 0, j = 0; i < index->noFiles; i++) {
        if(GET_BIT(index->found[0], i)) {
            results[j].filename = index->filenames[i];
            results[j].score = index->tfidf[0][i];
            j++;
        }
    }
    qsort(results, noFound, sizeof(TResult), resultComp);
    for(size_t i = 0; i < noFound; i++) {
        printf("%s, tfidf = %f\n", results[i].filename, results[i].score);
    }
    free(results);
}

void freeIndex(invertedIndex *index)
{
    if(index == NULL) {
        return;
    }
    for(size_t i = 0; i < index->noTerms; i++) {
        if(index->terms && index->terms[i]) {
            free(index->terms[i]);
        }
        if(index->found && index->found[i]) {
            free(index->found[i]);
        }
        if(index->tfidf && index->tfidf[i]) {
            free(index->tfidf[i]);        
        }
    }
    if(index->terms) {
        free(index->terms);
    }
    if(index->found) {
        free(index->found);
    }
    if(index->tfidf) {
        free(index->tfidf);
    }
    for(size_t i = 0; i < index->noFiles; i++) {
        if(index->filenames && index->filenames[i]) {
            free(index->filenames[i]);
        }
    }
    if(index->filenames) {
        free(index->filenames);
    }
    free(index);
}
