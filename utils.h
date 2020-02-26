#ifndef UTILS_H
#define UTILS_H

#include "bitarray.h"

#define MAX(a, b) ( (a) > (b) ? (a) : (b) )
#define BUF_SIZE 4096
#define MAX_TERMS 20
#define MAX_OP 100

typedef struct {
    char **terms, **filenames;
    float **tfidf;
    bitarray *found;
    size_t noTerms, noFiles;
} invertedIndex;

typedef struct {
    char *filename;
    float score;
} TResult; 

int resultComp(const void *a, const void *b);

#endif
