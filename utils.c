#include "utils.h"

int resultComp(const void *a, const void *b)
{
    if(((TResult *) a)->score < ((TResult *) b)->score) {
        return 1;
    }
    else if (((TResult *) a)->score == ((TResult *) b)->score) {
        return 0;
    }
    else {
        return -1;
    }
}
