#ifndef PARSE_H
#define PARSE_H

#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "stack.h"

/* main function used for parsing the input string "str". 
 * the function uses the shunting yard algorithm.
 * returns the address of index->found[0], where the resulting bitarray is located. */
bitarray parseString(char *str, invertedIndex *index);
/* adds an operator "op" to the "operators" stack, removes elements with
 * lower or equal priorities from top */
void addOperator(invertedIndex *index, TStack *operators, TStack *terms, char op);
/* does all the operations scheduled after the start of the last parenthesis */
void closeParentheses(invertedIndex *index, TStack *operators, TStack *terms);
/* does all the operations remaining in the "operators" stack */
void finishOperations(invertedIndex *index, TStack *operators, TStack *terms);

#endif
