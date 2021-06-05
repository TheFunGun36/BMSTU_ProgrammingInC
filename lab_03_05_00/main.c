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

    for (size_t i = 0; i < *size_y; i++)
    {
        for (size_t j = 0; j < *size_x; j++)
        {
            if (scanf("%d", &matrix[i][j]) != 1)
                return INVALID_MATRIX_ELEMENT;
        }
    }

    return OK;
}

int is_prime(int value)
{
    if ((value != 2 && !(value % 2)) || value <= 1)
        return 0;

    for (int i = 3; i * i <= value; i += 2)
        if (!(value % i))
            return 0;

    return 1;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void form_prime_array(int matrix[][MAX_MATRIX_SIZE_X], size_t size_x, size_t size_y, int prime_array[], size_t *arr_size)
{
    size_t new_array_size = 0;

    for (size_t i = 0; i < size_y; i++)
    {
        for (size_t j = 0; j < size_x; j++)
        {
            if (is_prime(matrix[i][j]))
            {
                prime_array[new_array_size] = matrix[i][j];
                matrix[i][j] = 2;
                new_array_size++;
            }
        }
    }

    *arr_size = new_array_size;
}

void reverse_array(int array[], int array_size)
{
    int *first = array;
    int *last = array + array_size - 1;

    while (first < last)
    {
        swap(first++, last--);
    }
}

void put_array_in_matrix(int matrix[][MAX_MATRIX_SIZE_X], size_t size_x, size_t size_y, int *prime_array)
{
    for (size_t i = 0; i < size_y; i++)
    {
        for (size_t j = 0; j < size_x; j++)
        {
            if (matrix[i][j] == 2)
                matrix[i][j] = *prime_array++;
        }
    }
}

void print_matrix(int matrix[][MAX_MATRIX_SIZE_X], size_t size_x, size_t size_y)
{
    for (size_t i = 0; i < size_y; i++)
    {
        for (size_t j = 0; j < size_x; j++)
        {
            printf("%d ", matrix[i][j]);
        }

        printf("\n");
    }
}

int main()
{
    int matrix[MAX_MATRIX_SIZE_Y][MAX_MATRIX_SIZE_X];
    size_t matrix_size_x, matrix_size_y;

    int prime_array[MAX_MATRIX_SIZE_X * MAX_MATRIX_SIZE_Y];
    size_t prime_array_size;

    int exit_code = get_matrix_from_user(matrix, &matrix_size_x, &matrix_size_y);

    if (exit_code != OK)
        return exit_code;

    form_prime_array(matrix, matrix_size_x, matrix_size_y, prime_array, &prime_array_size);

    if (prime_array_size <= 0)
    {
        exit_code = NO_PRIME_NUMBERS;
    }
    else
    {
        reverse_array(prime_array, prime_array_size);
        put_array_in_matrix(matrix, matrix_size_x, matrix_size_y, prime_array);
        print_matrix(matrix, matrix_size_x, matrix_size_y);
    }

    return exit_code;
}
