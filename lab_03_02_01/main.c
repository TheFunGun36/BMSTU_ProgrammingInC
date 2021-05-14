#include <stdio.h>

#define MAX_MATRIX_SIZE_X 10
#define MAX_MATRIX_SIZE_Y 10

#define OK 0
#define INVALID_SZ_X -1
#define INVALID_SZ_Y -2
#define INVALID_MATRIX_ELEMENT -3

int get_matrix_from_user(int matrix[][MAX_MATRIX_SIZE_X], size_t *size_x, size_t *size_y)
{
    if (scanf("%lud", size_y) != 1 || *size_y <= 1 || *size_y > MAX_MATRIX_SIZE_Y)
        return INVALID_SZ_Y;

    if (scanf("%lud", size_x) != 1 || *size_x <= 1 || *size_x > MAX_MATRIX_SIZE_X)
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

int calculate_digit_sum(int value)
{
    if (value < 0)
        value *= -1;

    int sum = 0;

    while (value > 0)
    {
        sum += value % 10;
        value /= 10;
    }

    return sum;
}

void find_min_digit_sum_element(int matrix[][MAX_MATRIX_SIZE_X], size_t size_x, size_t size_y, unsigned int *pos_x, unsigned int *pos_y)
{
    int last_sum = calculate_digit_sum(matrix[0][0]);
    unsigned int best_pos_x = 0;
    unsigned int best_pos_y = 0;

    for (unsigned int i = 0; i < size_y; i++)
    {
        for (unsigned int j = 0; j < size_x; j++)
        {
            int current_sum = calculate_digit_sum(matrix[i][j]);

            if (current_sum < last_sum)
            {
                best_pos_x = j;
                best_pos_y = i;
                last_sum = current_sum;
            }
        }
    }

    *pos_x = best_pos_x;
    *pos_y = best_pos_y;
}

void remove_matrix_row(int matrix[][MAX_MATRIX_SIZE_X], unsigned int row, size_t *size_x, size_t *size_y)
{
    for (unsigned int j = 0; j < *size_x; j++)
    {
        for (unsigned int i = row + 1; i < *size_y; i++)
        {
            matrix[i - 1][j] = matrix[i][j];
        }
    }

    (*size_y)--;
}

void remove_matrix_column(int matrix[][MAX_MATRIX_SIZE_X], unsigned int column, size_t *size_x, size_t *size_y)
{
    for (unsigned int i = 0; i < *size_y; i++)
    {
        for (unsigned int j = column + 1; j < *size_x; j++)
        {
            matrix[i][j - 1] = matrix[i][j];
        }
    }

    (*size_x)--;
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

    unsigned int min_num_x, min_num_y;
    find_min_digit_sum_element(matrix, size_x, size_y, &min_num_x, &min_num_y);

    remove_matrix_column(matrix, min_num_x, &size_x, &size_y);
    remove_matrix_row(matrix, min_num_y, &size_x, &size_y);

    print_matrix(matrix, size_x, size_y);

    return exit_code;
}
