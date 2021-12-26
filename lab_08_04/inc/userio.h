#ifndef USER_INPUT_H
#define USER_INPUT_H

#include "matrix.h"

exit_t input_matrix(matrix_t *matrix);
exit_t input_uint(unsigned int *value, char is_zero_allowed);

exit_t print_matrix(const matrix_t *matrix);

#endif
