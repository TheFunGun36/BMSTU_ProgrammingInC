#include "matrix.h"
#include <string.h>

static uint32_t matrix_find_max(const matrix_t *matrix, char is_should_find_row);
static void matrix_delete_row(matrix_t *matrix, uint32_t row);
static void matrix_delete_col(matrix_t *matrix, uint32_t col);
static int matrix_col_arithmetic_mean(const matrix_t *matrix, uint32_t col);
static int matrix_row_min(const matrix_t *matrix, uint32_t row);
static exit_t matrix_add_rows(matrix_t *matrix, uint32_t amount);
static exit_t matrix_add_cols(matrix_t *matrix, uint32_t amount);
static int matrix_mul_single_el(const matrix_t *first, const matrix_t *second, uint32_t row, uint32_t col);
static void matrix_to_unit(matrix_t *matrix);

exit_t matrix_initialize(int ***matrix, uint32_t rows, uint32_t cols)
{
    exit_t exit_code = exit_success;

    *matrix = (int**)calloc(rows, sizeof(int*));

    if (matrix)
    {
        int **pp_end = *matrix + rows;
        for (int **pp = *matrix; exit_code == exit_success && pp < pp_end; pp++)
        {
            *pp = (int*)malloc(cols * sizeof(int));

            if (!*pp)
                exit_code = exit_no_memory;
        }

        if (exit_code != exit_success)
        {
            matrix_t mtx = {rows, cols, *matrix};
            matrix_free(&mtx);
            *matrix = NULL;
        }
    }
    else
    {
        exit_code = exit_no_memory;
    }

    return exit_code;
}

exit_t matrix_to_square(matrix_t *matrix)
{
    while (matrix->rows > matrix->cols)
    {
        uint32_t row = matrix_find_max(matrix, 1);
        matrix_delete_row(matrix, row);
    }

    while (matrix->cols > matrix->rows)
    {
        uint32_t col = matrix_find_max(matrix, 0);
        matrix_delete_col(matrix, col);
    }

    return exit_success;
}

exit_t matrix_to_same_size(matrix_t *first, matrix_t *second)
{
    exit_t exit_code = exit_success;

    int delta_rows = first->rows - second->rows;

    if (delta_rows > 0)
        exit_code = matrix_add_rows(second, delta_rows);
    else if (delta_rows < 0)
        exit_code = matrix_add_rows(first, -delta_rows);

    if (exit_code == exit_success)
    {
        int delta_cols = first->cols - second->cols;

        if (delta_cols > 0)
            exit_code = matrix_add_cols(second, delta_cols);
        else if (delta_cols < 0)
            exit_code = matrix_add_cols(first, -delta_cols);
    }

    return exit_code;
}

exit_t matrix_pow(matrix_t *matrix, uint32_t power)
{
    exit_t exit_code = exit_success;

    if (matrix->rows != matrix->cols)
    {
        exit_code = exit_internal_error;
    }
    else if (power == 0)
    {
        matrix_to_unit(matrix);
    }
    else if (power != 1 && power % 2)
    {
        matrix_t squared = {0};
        exit_code = matrix_multiply(matrix, matrix, &squared);

        if (exit_code == exit_success)
            exit_code = matrix_pow(&squared, power / 2);
        
        matrix_t result = {0};
        if (exit_code == exit_success)
            exit_code = matrix_multiply(matrix, &squared, &result);

        if (exit_code == exit_success)
        {
            matrix_free(&squared);
            matrix_free(matrix);
            *matrix = result;
        }
        else
        {
            matrix_free(&squared);
            matrix_free(&result);
        }
    }
    else if (!(power % 2))
    {
        matrix_t result = {0};
        exit_code = matrix_multiply(matrix, matrix, &result);

        if (exit_code == exit_success)
            exit_code = matrix_pow(&result, power / 2);

        if (exit_code == exit_success)
        {
            matrix_free(matrix);
            *matrix = result;
        }
        else
        {
            matrix_free(&result);
        }
    }

    return exit_code;
}

exit_t matrix_multiply(const matrix_t *first, const matrix_t *second, matrix_t *result)
{
    exit_t exit_code = exit_success;

    if (first->cols != second->rows)
        exit_code = exit_internal_error;
    else
        exit_code = matrix_initialize(&result->element, first->rows, second->cols);

    if (exit_code == exit_success)
    {
        result->rows = first->rows;
        result->cols = second->cols;

        int **pp_end = result->element + result->rows;
        for (int **pp = result->element, i = 0; pp < pp_end; pp++, i++)
        {
            int *p_end = *pp + result->cols;
            for (int *p = *pp, j = 0; p < p_end; p++, j++)
                *p = matrix_mul_single_el(first, second, i, j);
        }
    }

    return exit_code;
}

void matrix_free(matrix_t *matrix)
{
    int **pp = matrix->element;

    if (pp != NULL)
    {
        int **pp_end = matrix->element + matrix->rows;
        for (; pp < pp_end; pp++)
            free(*pp);
    }

    free(matrix->element);

    memset(matrix, 0, sizeof(matrix_t));
}

static uint32_t matrix_find_max(const matrix_t *matrix, char is_should_find_row)
{
    uint32_t result = 0;
    int max_element = **matrix->element;

    for (uint32_t j = 0; j < matrix->cols; j++)
    {
        for (uint32_t i = 0; i < matrix->rows; i++)
        {
            int cur_element = *(*(matrix->element + i) + j);

            if (cur_element >= max_element)
            {
                if (is_should_find_row)
                    result = i;
                else
                    result = j;

                max_element = cur_element;
            }
        }
    }

    return result;
}

void matrix_delete_row(matrix_t *matrix, uint32_t row)
{
    int **pp = matrix->element + row;
    free(*pp);

    int **pp_end = matrix->element + --matrix->rows;

    while (pp < pp_end)
    {
        *pp = *(pp + 1);
        pp++;
    }
}

void matrix_delete_col(matrix_t *matrix, uint32_t col)
{
    int **pp_end = matrix->element + matrix->rows;
    matrix->cols--;

    for (int **pp = matrix->element; pp < pp_end; pp++)
    {
        int *p_end = *pp + matrix->cols;
        for (int *p = *pp + col; p < p_end; p++)
            *p = *(p + 1);
    }
}

int matrix_col_arithmetic_mean(const matrix_t *matrix, uint32_t col)
{
    int result = 0;

    int **pp_end = matrix->element + matrix->rows;
    for (int **pp = matrix->element; pp < pp_end; pp++)
        result += *(*pp + col);

    return result / matrix->rows;
}

int matrix_row_min(const matrix_t *matrix, uint32_t row)
{
    int **pp = matrix->element + row;
    int result = **pp;

    int *p_end = *pp + matrix->cols;
    for (int *p = *pp + 1; p < p_end; p++)
        if (*p < result)
            result = *p;

    return result;
}

static exit_t matrix_add_rows(matrix_t *matrix, uint32_t amount)
{
    exit_t exit_code = exit_success;
    uint32_t new_rows = matrix->rows + amount;

    int **new_element = (int**)realloc(matrix->element, new_rows * sizeof(int*));

    if (new_element)
    {
        matrix->element = new_element;
        int **pp_end = matrix->element + new_rows;
        int **pp = matrix->element + matrix->rows;
        for (; exit_code == exit_success && pp < pp_end; pp++, matrix->rows++)
        {
            *pp = malloc(matrix->cols * sizeof(int));

            int *p_end = *pp + matrix->cols;
            for (int *p = *pp, col = 0; p < p_end; p++, col++)
                *p = matrix_col_arithmetic_mean(matrix, col);
        }
    }
    else
    {
        exit_code = exit_no_memory;
    }

    return exit_code;
}

static exit_t matrix_add_cols(matrix_t *matrix, uint32_t amount)
{
    exit_t exit_code = exit_success;
    uint32_t new_cols = matrix->cols + amount;

    int **pp_end = matrix->element + matrix->rows;
    for (int **pp = matrix->element, i = 0; exit_code == exit_success && pp < pp_end; pp++, i++)
    {
        int *new_p = (int*)realloc(*pp, new_cols * sizeof(int));

        if (new_p)
        {
            *pp = new_p;
            int min_el = matrix_row_min(matrix, i);
            int *p_end = *pp + matrix->cols + amount;

            for (int *p = *pp + matrix->cols; p < p_end; p++)
                *p = min_el;
        }
        else
        {
            exit_code = exit_no_memory;
        }
    }

    if (exit_code == exit_success)
        matrix->cols += amount;

    return exit_code;
}

int matrix_mul_single_el(const matrix_t *first, const matrix_t *second, uint32_t row, uint32_t col)
{
    int result = 0;

    for (int i = 0, *fp = *(first->element + row); i < first->cols; i++, fp++)
        result += (*fp) * (*(*(second->element + i) + col));

    return result;
}

void matrix_to_unit(matrix_t *matrix)
{
    int **pp_end = matrix->element + matrix->rows;
    for (int **pp = matrix->element, i = 0; pp < pp_end; pp++, i++)
    {
        int *p_end = *pp + matrix->cols;
        for (int *p = *pp, j = 0; p < p_end; p++, j++)
            *p = i == j;
    }
}
