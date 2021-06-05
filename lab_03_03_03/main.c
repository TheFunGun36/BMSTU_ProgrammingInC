#include <stdio.h>

#define MAX_MATRIX_SIZE_X 10
#define MAX_MATRIX_SIZE_Y 10

#define OK 0
#define INVALID_SZ_X -1
#define INVALID_SZ_Y -2
#define INVALID_MATRIX_ELEMENT -3

int get_matrix_from_user(int matrix[][MAX_MATRIX_SIZE_X], size_t *size_x, size_t *size_y)
{
    if (scanf("%lud", size_y) != 1 || *size_y <= 0 || *size_y > MAX_MATRIX_SIZE_Y)
        return INVALID_SZ_Y;

    if (scanf("%lud", size_x) != 1 || *size_x <= 0 || *size_x >= MAX_MATRIX_SIZE_X)
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

int get_row_min_element(int matrix[][MAX_MATRIX_SIZE_X], size_t size_x, unsigned int row)
{
    int result = matrix[row][0];

    for (unsigned int i = 0; i < size_x; i++)
    {
        if (matrix[row][i] < result)
            result = matrix[row][i];
    }

    return result;
}

void calculate_sort_keys(int matrix[][MAX_MATRIX_SIZE_X], size_t size_x, size_t size_y, int sort_keys[])
{
    for (unsigned int i = 0; i < size_y; i++)
        sort_keys[i] = get_row_min_element(matrix, size_x, i);
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void swap_rows(int matrix[][MAX_MATRIX_SIZE_X], size_t size_x, unsigned int row1, unsigned int row2)
{
    for (unsigned int i = 0; i < size_x; i++)
        swap(&matrix[row1][i], &matrix[row2][i]);
}

void sort_matrix(int matrix[][MAX_MATRIX_SIZE_X], size_t size_x, size_t size_y)
{
    int sort_keys[MAX_MATRIX_SIZE_Y];

    calculate_sort_keys(matrix, size_x, size_y, sort_keys);

    for (size_t i = 0; i < size_y; i++)
    {
        size_t best_index = i;

        for (size_t j = i + 1; j < size_y; j++)
        {
            if (sort_keys[best_index] < sort_keys[j])
                best_index = j;
        }

        if (best_index != i)
        {
            swap_rows(matrix, size_x + 1, i, best_index);
            swap(&sort_keys[i], &sort_keys[best_index]);
        }
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
