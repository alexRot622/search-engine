#include "stack.h"

TStack *allocStack(size_t maxSz)
{
    TStack *stack;

    stack = (TStack *) malloc(sizeof(TStack));
    if(stack == NULL) {
        return NULL;
    }
    stack->arr = (char *) malloc(maxSz);
    if(stack->arr == NULL) {
        free(stack);
        return NULL;
    }
    stack->currSz = 0;
    stack->maxSz = maxSz;
    return stack;
}

void freeStack(TStack *stack)
{
    if(stack->arr != NULL) {
        free(stack->arr);
    }
    free(stack);
}

int push(TStack *stack, char c)
{
    size_t currSz = stack->currSz, maxSz = stack->maxSz;

    if(currSz >= maxSz) {
        return -1;
    }
    stack->arr[currSz + 1] = c;
    stack->currSz++;
    return 0;
}

char pop(TStack *stack)
{
    char c = top(stack);

    stack->currSz--;
    return c;
}

char top(TStack *stack)
{
    return stack->arr[stack->currSz];
}
