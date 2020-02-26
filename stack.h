#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

typedef struct {
    char *arr;
    size_t currSz, maxSz;
} TStack;

TStack *allocStack(size_t maxSz);
void freeStack(TStack *stack);
int push(TStack *stack, char c);
char pop(TStack *stack);
char top(TStack *stack);
#endif
