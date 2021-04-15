#include <stdio.h>

#define MAX_MATRIX_SIZE_X 10
#define MAX_MATRIX_SIZE_Y 10

#define OK 0
#define INVALID_SZ_X -1
#define INVALID_SZ_Y -2
#define MATRIX_SIZE_ONE -3

int get_matrix_size(size_t *size_x, size_t *size_y)
{
    if (scanf("%lud", size_y) != 1 || *size_y <= 0 || *size_y > MAX_MATRIX_SIZE_Y)
        return INVALID_SZ_Y;

    if (scanf("%lud", size_x) != 1 || *size_x <= 0 || *size_x > MAX_MATRIX_SIZE_X)
        return INVALID_SZ_X;

    if (*size_x == 1 && *size_y == 1)
        return MATRIX_SIZE_ONE;
    
    return OK;
}

void create_matrix(int matrix[][MAX_MATRIX_SIZE_X], size_t size_x, size_t size_y)
{
    int current_number = 1;

    int min_size = size_x * (size_x < size_y) + size_y * (size_y <= size_x);

    for (int cycle = 0; cycle < min_size / 2; cycle++)
    {
        for (int i = cycle; i < (int)size_x - cycle - 1; i++)
        {
            matrix[cycle][i] = current_number;
            current_number++;
        }

        for (int i = cycle; i < (int)size_y - cycle - 1; i++)
        {
            matrix[i][size_x - cycle - 1] = current_number;
            current_number++;
        }

        for (int i = size_x - cycle - 1; i >= cycle + 1; i--)
        {
            matrix[size_y - cycle - 1][i] = current_number;
            current_number++;
        }

        for (int i = size_y - cycle - 1; i >= cycle + 1; i--)
        {
            matrix[i][cycle] = current_number;
            current_number++;
        }
    }

    if (min_size & 1)
    {
        int cycle = min_size / 2;

        for (unsigned int i = cycle; i < size_x - cycle - 1; i++)
        {
            matrix[cycle][i] = current_number;
            current_number++;
        }

        for (unsigned int i = cycle; i < size_y - cycle; i++)
        {
            matrix[i][size_x - cycle - 1] = current_number;
            current_number++;
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

    int exit_code = get_matrix_size(&size_x, &size_y);

    if (exit_code != OK)
        return exit_code;

    create_matrix(matrix, size_x, size_y);

    print_matrix(matrix, size_x, size_y);

    return exit_code;
}