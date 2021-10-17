#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <inttypes.h>
#include "exit_code.h"

typedef struct
{
    uint32_t rows;
    uint32_t cols;

    int **element;
} matrix_t;

exit_t matrix_initialize(int ***matrix, uint32_t rows, uint32_t cols);
exit_t matrix_to_square(matrix_t *matrix);
exit_t matrix_to_same_size(matrix_t *first, matrix_t *second);
exit_t matrix_pow(matrix_t *matrix, uint32_t power);
exit_t matrix_multiply(const matrix_t *matrix_a, const matrix_t *matrix_b, matrix_t *result);
void matrix_free(matrix_t *matrix);

#endif
