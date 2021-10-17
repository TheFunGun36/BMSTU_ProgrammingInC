#include <stdio.h>
#include "userio.h"
#include "matrix.h"

#define IF_SUCCESS_CALL(x) if (exit_code == exit_success) exit_code = (x)

int main()
{
    matrix_t matrix_a = {0};
    matrix_t matrix_b = {0};
    matrix_t matrix_result = {0};

    exit_t exit_code = exit_success;
    
    IF_SUCCESS_CALL(input_matrix(&matrix_a));
    IF_SUCCESS_CALL(matrix_to_square(&matrix_a));
    
    IF_SUCCESS_CALL(input_matrix(&matrix_b));
    IF_SUCCESS_CALL(matrix_to_square(&matrix_b));

    IF_SUCCESS_CALL(matrix_to_same_size(&matrix_a, &matrix_b));
    
    unsigned int a_pow, b_pow;

    IF_SUCCESS_CALL(input_uint(&a_pow, 1));
    IF_SUCCESS_CALL(matrix_pow(&matrix_a, a_pow));

    IF_SUCCESS_CALL(input_uint(&b_pow, 1));
    IF_SUCCESS_CALL(matrix_pow(&matrix_b, b_pow));

    IF_SUCCESS_CALL(matrix_multiply(&matrix_a, &matrix_b, &matrix_result));

    IF_SUCCESS_CALL(print_matrix(&matrix_result));

    matrix_free(&matrix_a);
    matrix_free(&matrix_b);
    matrix_free(&matrix_result);

    return exit_code;
}
