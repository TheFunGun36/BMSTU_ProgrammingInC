#include <stdio.h>

#define ARR_SIZE 10
#define ARR_SIZE_MAX 20

#define OK 0
#define WRONG_INPUT -1
#define WRONG_ARRAY_SIZE -2

void get_next_fib(int *first, int *second);
int start_input_loop(int *array, int *arr_size);
void print_array(int *array, int arr_size);

int main()
{
    int array[ARR_SIZE_MAX];
    int arr_size;
    int exit_code = start_input_loop(array, &arr_size);
    
    if (exit_code != OK)
        return exit_code;

    print_array(array, arr_size);
    return exit_code;
}

void get_next_fib(int *first, int *second)
{
    int next_number = *first + *second;
    *first = *second;
    *second = next_number;
}

int start_input_loop(int *array, int *arr_size)
{
    if (scanf("%d", arr_size) != 1)
        return WRONG_ARRAY_SIZE;

    if (*arr_size <= 0 || *arr_size > 10)
        return WRONG_ARRAY_SIZE;

    int fib_0 = 0;
    int fib_1 = 1;

    for (int i = 0; i < *arr_size; i++)
    {
        int result = scanf("%d", &array[i]);
        
        if (result != 1)
            return WRONG_INPUT;

        if (array[i] % 3 == 0)
        {
            i++;
            (*arr_size)++;
            array[i] = fib_0;
            get_next_fib(&fib_0, &fib_1);
        }
    }

    return OK;
}

void print_array(int *array, int arr_size)
{
    for (int i = 0; i < arr_size; i++)
        printf("%d ", array[i]);
}
