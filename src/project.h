/*
maxof(t) returns the maximum value of an int type t
*/
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

#define isfloat(t) ((t)1/2 > 0)

#define issigned(t) (((t)(-1)) < ((t) 0))

#define umaxof(t) (((0x1ULL << ((sizeof(t) * 8ULL) - 1ULL)) - 1ULL) | \
                    (0xFULL << ((sizeof(t) * 8ULL) - 4ULL)))

#define smaxof(t) (((0x1ULL << ((sizeof(t) * 8ULL) - 1ULL)) - 1ULL) | \
                    (0x7ULL << ((sizeof(t) * 8ULL) - 4ULL)))

#define maxof(t) ((unsigned long long) (issigned(t) ? smaxof(t) : umaxof(t)))

#define typecode(t) (uint8_t)(isfloat(t) + (issigned(t) << 1) + (sizeof(t) << 2))

#define size(t) sizeof(t)/sizeof(t*)
