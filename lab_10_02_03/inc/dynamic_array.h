#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>

#define DARR_MEMORY_INC 8

#define ARR_OK 0
#define ARR_NO_MEMORY 1
#define ARR_INVALID_PTR 2

typedef struct
{
    int *data;
    size_t size;
    size_t allocated;
} int_darr_t;

int int_darr_add(int_darr_t *darr, int val);
void int_darr_free(int_darr_t *darr);

#endif
