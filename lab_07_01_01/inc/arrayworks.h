#ifndef ARRAYWORKS_H
#define ARRAYWORKS_H

#include <stdio.h>

void mysort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*));

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

int filter_array(int **arr_begin, int **arr_end);

void safe_free(int **arr_begin, int **arr_end);

int compar_ascend(const void *a, const void *b);

#endif
