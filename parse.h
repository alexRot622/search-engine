#ifndef PARSE_H
#define PARSE_H

#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "stack.h"

bitarray parseString(char *str, invertedIndex *index);
void addOperator(invertedIndex *index, TStack *operators, TStack *terms, char op);
void closeParant(invertedIndex *index, TStack *operators, TStack *terms);
void finishOperations(invertedIndex *index, TStack *operators, TStack *terms);
float getTFIDF(invertedIndex *index); //TODO

#endif
