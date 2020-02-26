#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "utils.h"
#include "bitarray.h"
#include "search.h"
#include "parse.h"

/* DEBUG */
void printBitarray(bitarray arr, size_t len)
{
    for(size_t i = 0; i < len; i++) {
        printf("%d", GET_BIT(arr, i));
    }
}

void printTfidf(invertedIndex *index)
{
    for(size_t i = 0; i < index->noTerms; i++) {
        printf("TERM[%lu]: \"%s\"\n", i, index->terms[i]);
        for(size_t j = 0; j < index->noFiles; j++) {
            if(GET_BIT(index->found[i], j)) {
                printf("\tFILE[%lu] = \"%s\", tfidf = %f\n", j, index->filenames[j], index->tfidf[i][j]);
            }   
        }
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
        printf("RES[%lu]: \"%s\", tfidf = %f\n", i, results[i].filename, results[i].score);
    }
    free(results);
}


//int main(int argc, char *argv[])
int main()
{
    invertedIndex index;
    //bitarray result;
    char *string, *dirname;

    string = (char *) malloc(BUF_SIZE);
    if(string == NULL) {
        fprintf(stderr, "ERROR: Could not allocate memory\n");
        exit(-1);
    }
    dirname = (char *) malloc(BUF_SIZE);
    if(dirname == NULL) {
        fprintf(stderr, "ERROR: Could not allocate memory\n");
        free(string);
        exit(-1);
    }
    fgets(string, BUF_SIZE, stdin);
    scanf("%s", dirname);
    index.terms = getTerms(string, &index.noTerms);
    index.noFiles = countFiles(dirname);
    index.found = (bitarray *) malloc(index.noTerms * sizeof(bitarray));
    for(size_t i = 0; i < index.noTerms; i++) {
        index.found[i] = calloc(INDEX(index.noFiles), sizeof(size_t));
    }
    index.filenames = (char **) malloc(index.noFiles * sizeof(char *));
    if(index.filenames == NULL) {
        fprintf(stderr, "ERROR: Could not allocate memory\n");
        exit(-1);
    }
    if(searchDir(&index, dirname)) {
        fprintf(stderr, "ERROR: Could not open directory \"%s\"\n", dirname);
        exit(-1);
    }
    parseString(string, &index);
    /*
    printf("RESULT: ");
    printBitarray(result, index.noFiles);
    printf("\n");*/


    showResults(&index);
    for(size_t i = 0; i < index.noTerms; i++) {
        free(index.terms[i]);
    }
    free(index.terms);
    for(size_t i = 0; i < index.noTerms; i++) {
        //printBitarray(index.found[i], index.noFiles);
        //printf("\n");
        free(index.found[i]);
        free(index.tfidf[i]);
    }
    free(index.found);
    free(index.tfidf);
    for(size_t i = 0; i < index.noFiles; i++) {
        //printf("DEBUG: filenames[%lu] = \"%s\"\n", i, index.filenames[i]);
        free(index.filenames[i]);
    }
    free(index.filenames);
    free(string);
    free(dirname);
    return 0;
}

