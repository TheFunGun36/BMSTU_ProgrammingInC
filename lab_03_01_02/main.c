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

void process_matrix_to_array(int matrix[][MAX_MATRIX_SIZE_X], size_t size_x, size_t size_y, int result[])
{
    if (size_y == 1)
    {
        for (size_t i = 0; i < size_x; i++)
            result[i] = 0;
    }
    else
    {
        for (unsigned int i = 0; i < size_x; i++)
        {
            if (matrix[0][i] == 0)
            {
                result[i] = 0;
            }
            else
            {
                int is_last_positive = (matrix[0][i] > 0);

                result[i] = 1;

                for (unsigned int j = 1; j < size_y && result[i]; j++)
                {
                    if (matrix[j][i] == 0)
                        result[i] = 0;
                    else if ((is_last_positive && (matrix[j][i] > 0)) || (!is_last_positive && (matrix[j][i] < 0)))
                        result[i] = 0;
                    else
                        is_last_positive = !is_last_positive;
                }
            }
        }
    }
}

void print_array(int array[], size_t size_x)
{
    for (unsigned int i = 0; i < size_x; i++)
        printf("%d ", array[i]);
}

int main()
{
    int matrix[MAX_MATRIX_SIZE_Y][MAX_MATRIX_SIZE_X];
    int result_array[MAX_MATRIX_SIZE_X];
    size_t size_x, size_y;

    int exit_code = get_matrix_from_user(matrix, &size_x, &size_y);

    if (exit_code != OK)
        return exit_code;

    process_matrix_to_array(matrix, size_x, size_y, result_array);
    print_array(result_array, size_x);

    return exit_code;
}
