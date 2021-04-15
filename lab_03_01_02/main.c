#include <stdio.h>

#define MAX_MATRIX_SIZE_X 10
#define MAX_MATRIX_SIZE_Y 10

#define OK 0
#define INVALID_SZ_X -1
#define INVALID_SZ_Y -2
#define INVALID_MATRIX_ELEMENT -3
#define NO_PRIME_NUMBERS -4

int get_matrix_from_user(int matrix[][MAX_MATRIX_SIZE_X], size_t *size_x, size_t *size_y)
{
    if (scanf("%lud", size_y) != 1 || *size_y <= 0 || *size_y > MAX_MATRIX_SIZE_Y)
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

void reconstruct_matrix(int matrix[][MAX_MATRIX_SIZE_X], size_t size_x, size_t size_y)
{
    for (unsigned int i = 0; i < size_x; i++)
    {   
        if (matrix[0][i] != 0)
        {
            int is_last_positive = (matrix[0][i] > 0);

            matrix[0][i] = 1;

            for (unsigned int j = 1; j < size_y && matrix[0][i]; j++)
            {
                if (matrix[j][i] == 0)
                    matrix[0][i] = 0;
                else if ((is_last_positive && (matrix[j][i] > 0)) || (!is_last_positive && (matrix[j][i] < 0)))
                    matrix[0][i] = 0;
                else
                    is_last_positive = !is_last_positive;
            }
        }
    }
}

void print_first_line(int matrix[][MAX_MATRIX_SIZE_X], size_t size_x)
{
    for (unsigned int i = 0; i < size_x; i++)
        printf("%d ", matrix[0][i]);
}

int main()
{
    int matrix[MAX_MATRIX_SIZE_Y][MAX_MATRIX_SIZE_X];
    size_t size_x, size_y;

    int exit_code = get_matrix_from_user(matrix, &size_x, &size_y);

    if (exit_code != OK)
        return exit_code;

    reconstruct_matrix(matrix, size_x, size_y);
    print_first_line(matrix, size_x);

    return exit_code;
}
