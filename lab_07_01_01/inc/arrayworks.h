#ifndef ARRAYWORKS_H
#define ARRAYWORKS_H

#include <stdio.h>

// bubble mod 3, var 7
void mysort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*));

// only elements bewteen min and max element
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

int filter_array(int **arr_begin, int **arr_end);

void safe_free(int **arr_begin, int **arr_end);

int compar_ascend(const void *a, const void *b);

#endif
