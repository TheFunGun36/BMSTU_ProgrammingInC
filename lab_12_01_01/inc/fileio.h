#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>

int create_array_from_file(FILE *f, int **arr_begin, int **arr_end, void (*safe_free)(int **, int **));
int write_array_to_file(FILE *f, int *arr_begin, int *arr_end);

#endif
