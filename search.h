#ifndef SEARCH_H
#define SEARCH_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "utils.h"

/* searches all terms in all files in a directory. Returns 0 if successful */
int searchDir(invertedIndex *index, char *dirname);
/* searches for a string in a file. Returns the term frequency of the string */
float searchFile(char *str, char *filename);
/* returns number of regular files in a directory */
size_t countFiles(char *dirname);
/* returns search terms that appear in the input string */
char **getTerms(char *str, size_t *len);

#endif
