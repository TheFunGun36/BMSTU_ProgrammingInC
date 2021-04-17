#include <stdio.h>

#define ARR_SIZE 10
#define ARR_SIZE_MAX 20

#define OK 0
#define WRONG_INPUT -1
#define WRONG_ARRAY_SIZE -2

void get_next_fib(int *first, int *second);
int get_array_from_user(int *array, int *arr_size);
void shift_array(int *array, int arr_size, int element);
void insert_fibonachi_numbers(int *array, int *arr_size);
void print_array(int *array, int arr_size);

int main()
{
    int array[ARR_SIZE_MAX];
    int arr_size;
    int exit_code = get_array_from_user(array, &arr_size);
    
    if (exit_code != OK)
        return exit_code;

    insert_fibonachi_numbers(array, &arr_size);
    print_array(array, arr_size);
    return exit_code;
}

void get_next_fib(int *first, int *second)
{
    int next_number = *first + *second;
    *first = *second;
    *second = next_number;
}

int get_array_from_user(int *array, int *arr_size)
{
    if (scanf("%d", arr_size) != 1)
        return WRONG_ARRAY_SIZE;

    if (*arr_size <= 0 || *arr_size > 10)
        return WRONG_ARRAY_SIZE;

    for (int i = 0; i < *arr_size; i++)
    {
        if (scanf("%d", &array[i]) != 1)
            return WRONG_INPUT;
    }

    return OK;
}

void shift_array(int *array, int arr_size, int element)
{
    for (int i = arr_size - 1; i > element; i--)
    {
        array[i] = array[i - 1];
    }
}

void insert_fibonachi_numbers(int *array, int *arr_size)
{
    int fib1 = 0;
    int fib2 = 1;
    
    for (int i = 0; i < *arr_size; i++)
    {
        if (!(array[i] % 3))
        {
            shift_array(array, ++(*arr_size), ++i);
            array[i] = fib1;
            get_next_fib(&fib1, &fib2);
        }
    }
}

void print_array(int *array, int arr_size)
{
    for (int i = 0; i < arr_size; i++)
        printf("%d ", array[i]);
}
