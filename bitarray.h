#ifndef BITARRAY_H
#define BITARRAY_H

#include <stdlib.h>

typedef size_t * bitarray;

/* Number of bits in each location used by the bit array */
#define BITS ( sizeof(size_t) * 8 )

/* k -- index in a bit array */
/* Gets the location of the k-th bit */
#define INDEX(k) ( (k) / BITS )
/* Gets the bit in the location corresponding to k */
#define POS(k)   ( (k) % BITS )
/* Gets the corresponding bit in the next location */
#define NEXT(k)  ( (k) + BITS )

/* a -- bit array
 * k -- index in a bit array */
/* set value of k-th bit */
#define SET_BIT(a, k)   ( (a)[INDEX(k)] |= (1 << POS(k)) )
/* clear value of k-th bit */
#define CLEAR_BIT(a, k) ( (a)[INDEX(k)] &= ~(1 << POS(k)) )
/* gets value of k-th bit */
#define GET_BIT(a, k)   ( ((a)[INDEX(k)] & (1 << POS(k))) != 0 )


/* a -- bit array
 * n -- number of bits in a */
/* flips the values of all bits in a */
#define FLIP_BITS(a, n) for(size_t i = 1; i <= n; i = NEXT(i)) { \
                            (a)[INDEX(i)] = ~((a)[INDEX(i)]); \
                        }

/* a, b -- bit arrays
 * n    -- number of bits in a, b */
/* apply bitwise or on a and b, stores the result in a */
#define OR_BITARR(a, b, n) for(size_t i = 1; i <= n; i = NEXT(i)) { \
                            (a)[INDEX(i)] |= (b)[INDEX(i)]; \
                        }
/* apply bitwise and on a and b, stores the result in a */
#define AND_BITARR(a, b, n) for(size_t i = 1; i <= n; i = NEXT(i)) { \
                            (a)[INDEX(i)] &= (b)[INDEX(i)]; \
                        }

#endif
