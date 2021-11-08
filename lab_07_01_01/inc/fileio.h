#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>

int create_array_from_file(FILE *f, int **arr_begin, int **arr_end);
int write_array_to_file(FILE *f, int *arr_begin, int *arr_end);

#endif
