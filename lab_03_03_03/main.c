#include <stdio.h>

#define MAX_MATRIX_SIZE_X 10
#define MAX_MATRIX_SIZE_Y 11

#define OK 0
#define INVALID_SZ_X -1
#define INVALID_SZ_Y -2
#define INVALID_MATRIX_ELEMENT -3

int get_matrix_from_user(int matrix[][MAX_MATRIX_SIZE_X], size_t *size_x, size_t *size_y)
{
    if (scanf("%lud", size_y) != 1 || *size_y <= 0 || *size_y >= MAX_MATRIX_SIZE_Y)
        return INVALID_SZ_Y;

    if (scanf("%lud", size_x) != 1 || *size_x <= 0 || *size_x > MAX_MATRIX_SIZE_X)
        return INVALID_SZ_X;

    for (unsigned int i = 0; i < *size_y; i++)
    {
        for (unsigned int j = 0; j < *size_x; j++)
        {
            if (scanf("%d", &matrix[i][j]) != 1)
                return INVALID_MATRIX_ELEMENT;
        }
    }

    return OK;
}

int multiply_column_elements(int matrix[][MAX_MATRIX_SIZE_X], size_t size_y, unsigned int col)
{
    int result = 1;

    for (unsigned int i = 0; i < size_y; i++)
        result *= matrix[i][col];

    return result;
}

void swap_columns(int matrix[][MAX_MATRIX_SIZE_X], size_t size_y, unsigned int col1, unsigned int col2)
{
    for (unsigned int i = 0; i < size_y; i++)
    {
        int tmp = matrix[i][col1];
        matrix[i][col1] = matrix[i][col2];
        matrix[i][col2] = tmp;
    }
}

void sort_matrix(int matrix[][MAX_MATRIX_SIZE_X], size_t size_x, size_t size_y)
{
    for (unsigned int i = 0; i < size_x; i++)
    {
        matrix[size_y][i] = multiply_column_elements(matrix, size_y, i);
    }

    for (unsigned int i = 0; i < size_x; i++)
    {
        unsigned int best_index = i;

        for (unsigned int j = i + 1; j < size_x; j++)
        {
            if (matrix[size_y][i] > matrix[size_y][j])
                best_index = j;
        }

        if (best_index != i)
            swap_columns(matrix, size_y + 1, i, best_index);
    }
}

void print_matrix(int matrix[][MAX_MATRIX_SIZE_X], size_t size_x, size_t size_y)
{
    for (unsigned int i = 0; i < size_y; i++)
    {
        for (unsigned int j = 0; j < size_x; j++)
            printf("%d ", matrix[i][j]);

        printf("\n");    
    }
}

int main()
{
    int matrix[MAX_MATRIX_SIZE_Y][MAX_MATRIX_SIZE_X];
    size_t size_x, size_y;

    int exit_code = get_matrix_from_user(matrix, &size_x, &size_y);

    if (exit_code != OK)
        return exit_code;

    sort_matrix(matrix, size_x, size_y);

    print_matrix(matrix, size_x, size_y);

    return exit_code;
}
