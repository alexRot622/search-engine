#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

/* stack structure used for parsing input. each element is a char value */
typedef struct {
    char *arr;
    size_t currSz, maxSz;
} TStack;

/* creates a stack and returns its value */
TStack *allocStack(size_t maxSz);
/* frees stack */
void freeStack(TStack *stack);
/* adds an element to stack, function returns 0 if successful */
int push(TStack *stack, char c);
/* removes element from top and returns its value */
char pop(TStack *stack);
/* returns top value */
char top(TStack *stack);
#endif
