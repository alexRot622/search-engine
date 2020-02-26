#ifndef UTILS_H
#define UTILS_H

#include "bitarray.h"

#define MAX(a, b) ( (a) > (b) ? (a) : (b) )
#define BUF_SIZE 4096
#define MAX_TERMS 20
#define MAX_OP 100

/* Data structure used for information retrieval */
typedef struct {
    char **terms,     // contains search terms
         **filenames; // contains names of files searched
    float **tfidf;    // contains the TF-IDF score of each term-file pair 
    bitarray *found;  // contains a bitarray for each term
    size_t noTerms,   // number of terms read
           noFiles;   // number of files read
} invertedIndex;

void freeIndex(invertedIndex *index);

/* Data structure used for sorting results by score */
typedef struct {
    char *filename;
    float score; // contains score used for soring
} TResult; 

/* comparator function used for sorting */
int resultComp(const void *a, const void *b);

/* Prints results of search */
void showResults(invertedIndex *index);


#endif
