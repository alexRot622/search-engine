#ifndef SEARCH_H
#define SEARCH_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "utils.h"

int searchDir(invertedIndex *index, char *dirname);
float searchFile(char *str, char *filename);
size_t countFiles(char *dirname);
char **getTerms(char *str, size_t *len);

#endif
