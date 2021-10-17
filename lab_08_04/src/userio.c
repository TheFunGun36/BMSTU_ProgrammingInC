#include "userio.h"
#include <inttypes.h>
#include <stdio.h>

static exit_t input_int(int *value);
static exit_t print_int(int value, char end);

exit_t input_matrix(matrix_t *matrix)
{
    exit_t exit_code = input_uint(&matrix->rows, 0);

    if (exit_code == exit_success)
        exit_code = input_uint(&matrix->cols, 0);

    if (exit_code == exit_success)
        exit_code = matrix_initialize(&matrix->element, matrix->rows, matrix->cols);

    if (exit_code == exit_success)
    {
        int **pp_end = matrix->element + matrix->rows;

        for (int **pp = matrix->element; exit_code == exit_success && pp < pp_end; pp++)
        {
            int *p_end = *pp + matrix->cols;
            for (int *p = *pp; exit_code == exit_success && p < p_end; p++)
                exit_code = input_int(p);
        }

        if (exit_code != exit_success)
            matrix_free(matrix);
    }

    return exit_code;
}

exit_t input_uint(uint32_t *value, char is_zero_allowed)
{
    exit_t exit_code = exit_success;

    long long int tmp_value;

    int res = scanf("%lld", &tmp_value);

    if (res == 0)
        exit_code = exit_invalid_input;
    else if (res < 0)
        exit_code = exit_eof;
    else if (tmp_value < 0 || tmp_value > INT32_MAX || (!is_zero_allowed && tmp_value == 0))
        exit_code = exit_invalid_input;
    else
        *value = (uint32_t)tmp_value;

    return exit_code;
}

exit_t print_matrix(const matrix_t *matrix)
{
    exit_t exit_code = exit_success;

    int **pp_end = matrix->element + matrix->rows;

    for (int **pp = matrix->element; exit_code == exit_success && pp < pp_end; pp++)
    {
        int *p_end = *pp + matrix->cols;

        for (int *p = *pp; exit_code == exit_success && p < p_end; p++)
        {
            char ch_end = (p_end - p == 1) ? '\n' : ' ';
            exit_code = print_int(*p, ch_end);
        }
    }

    return exit_code;
}

exit_t input_int(int *value)
{
    exit_t exit_code = exit_success;

    int res = scanf("%d", value);

    if (res == 0)
        exit_code = exit_invalid_input;
    else if (res < 0)
        exit_code = exit_eof;

    return exit_code;
}

exit_t print_int(int value, char end)
{
    exit_t exit_code = exit_success;

    if (printf("%d%c", value, end) <= 1)
        exit_code = exit_output_failure;

    return exit_code;
}
