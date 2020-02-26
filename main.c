#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "bitarray.h"
#include "search.h"
#include "parse.h"

int main(int argc, char *argv[])
{
    invertedIndex *index;
    char *dirname = argv[1], *string = argv[2];

    if(argc <= 2) {
        printf("USAGE: ./search <DIRNAME> <STRING>\n");
        exit(-1);
    }
    index = (invertedIndex *) malloc(sizeof(invertedIndex));
    index->noTerms = index->noFiles = 0;
    index->terms = getTerms(string, &index->noTerms);
    index->noFiles = countFiles(dirname);

    index->filenames = (char **) malloc(index->noFiles * sizeof(char *));
    if(index->filenames == NULL) {
        freeIndex(index);
        fprintf(stderr, "ERROR: Could not allocate memory\n");
        exit(-1);
    }
    index->found = (bitarray *) malloc(index->noTerms * sizeof(bitarray));
    if(index->found == NULL) {
        freeIndex(index);
        fprintf(stderr, "ERROR: Could not allocate memory\n");
        exit(-1);
    }
    index->tfidf = (float **) malloc(index->noTerms * sizeof(float *));
    if(index->tfidf == NULL) {
        freeIndex(index);
        fprintf(stderr, "ERROR: Could not allocate memory\n");
        exit(-1);
    }
    for(size_t i = 0; i < index->noTerms; i++) {
        index->found[i] = calloc(INDEX(index->noFiles), sizeof(size_t));
        index->tfidf[i] = (float *) malloc(index->noFiles * sizeof(float *));
    }
    
    if(searchDir(index, dirname)) {
        fprintf(stderr, "ERROR: Could not open directory \"%s\"\n", dirname);
        exit(-1);
    }
    parseString(string, index);
    showResults(index);

    return 0;
}

