#include <stdio.h>

#define MAX_MATRIX_SIZE_X 10
#define MAX_MATRIX_SIZE_Y 10

#define OK 0
#define INVALID_SZ_X -1
#define INVALID_SZ_Y -2
#define INVALID_MATRIX_ELEMENT -3
#define NO_PRIME_NUMBERS -4

int get_matrix_from_user(int *matrix, size_t *size, size_t *size_x)
{
    {
        size_t size_y;
        
        if (scanf("%lud", &size_y) != 1 || size_y <= 0 || size_y > MAX_MATRIX_SIZE_Y)
            return INVALID_SZ_Y;

        if (scanf("%lud", size_x) != 1 || *size_x <= 0 || *size_x > MAX_MATRIX_SIZE_X)
            return INVALID_SZ_X;

        *size = *size_x * size_y;
    }

    for (unsigned int i = 0; i < *size; i++)
    {
        if (scanf("%d", &matrix[i]) != 1)
            return INVALID_MATRIX_ELEMENT;
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

int array_has_primes(int *array, size_t size)
{
    for (int i = 0; i < size; i++)
        if (is_prime(array[i]))
            return 1;

    return 0;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void reconstruct_matrix(int *matrix, size_t size)
{
    int *prime1 = matrix;
    int *prime2 = matrix + size;

    while (prime1 < prime2)
    {
        do
            prime1++;
        while (prime1 < prime2 && !is_prime(*prime1));
        
        do
            prime2--;
        while (prime1 < prime2 && !is_prime(*prime2));

        if (prime1 < prime2)
            swap(prime1, prime2);
    }
}

void print_matrix(int *matrix, size_t size, size_t size_x)
{
    for (unsigned int i = 0; i < size; i++)
    {
        printf("%d", matrix[i]);

        if ((i + 1) % size_x)
            printf(" ");
        else
            printf("\n");    
    }
}

int main()
{
    int array[MAX_MATRIX_SIZE_Y * MAX_MATRIX_SIZE_X];
    size_t array_size, matrix_size_x;

    int exit_code = get_matrix_from_user(array, &array_size, &matrix_size_x);

    if (exit_code != OK)
        return exit_code;

    if (array_has_primes(array, array_size))
    {
        reconstruct_matrix(array, array_size);
        print_matrix(array, array_size, matrix_size_x);
    }
    else
    {
        exit_code = NO_PRIME_NUMBERS;
    }

    return exit_code;
}
