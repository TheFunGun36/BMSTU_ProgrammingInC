#include <stdio.h>

#define MAX_MATRIX_SIZE_X 10
#define MAX_MATRIX_SIZE_Y 10

#define OK 0
#define INVALID_SZ -1
#define SIZES_NOT_EQUAL -2
#define INVALID_MATRIX_ELEMENT -3

int get_matrix_from_user(int matrix[][MAX_MATRIX_SIZE_X], size_t *size)
{
    if (scanf("%lud", size) != 1 || *size <= 0 || *size > MAX_MATRIX_SIZE_Y)
        return INVALID_SZ;

    size_t size_another;

    if (scanf("%lud", &size_another) != 1 || size_another != *size)
        return SIZES_NOT_EQUAL;

    for (unsigned int i = 0; i < *size; i++)
    {
        for (unsigned int j = 0; j < *size; j++)
        {
            if (scanf("%d", &matrix[i][j]) != 1)
                return INVALID_MATRIX_ELEMENT;
        }
    }

    return OK;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void transform_matrix(int matrix[][MAX_MATRIX_SIZE_X], size_t size)
{
    for (unsigned int j = 0; j < size; j++)
        for (unsigned int i = j; i < size - j; i++)
            swap(&matrix[i][j], &matrix[i][size - j - 1]);
}

void print_matrix(int matrix[][MAX_MATRIX_SIZE_X], size_t size)
{
    for (unsigned int i = 0; i < size; i++)
    {
        for (unsigned int j = 0; j < size; j++)
            printf("%d ", matrix[i][j]);

        printf("\n");    
    }
}

int main()
{
    int matrix[MAX_MATRIX_SIZE_Y][MAX_MATRIX_SIZE_X];
    size_t size;

    int exit_code = get_matrix_from_user(matrix, &size);

    if (exit_code != OK)
        return exit_code;

    transform_matrix(matrix, size);

    print_matrix(matrix, size);

    return exit_code;
}
