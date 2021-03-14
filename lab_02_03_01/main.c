#include <stdio.h>

#define ARR_SIZE 10
#define ARR_SIZE_MAX 20

#define OK 0
#define WRONG_INPUT -1

void get_next_fib(int *first, int *second);
int start_input_loop(int *array, int arr_size, int *arr_size_new);
void print_array(int *array, int arr_size);

int main()
{
    int array[ARR_SIZE_MAX];
    int arr_size_new;
    int exit_code = start_input_loop(array, ARR_SIZE, &arr_size_new);
    
    if (exit_code != OK)
        return exit_code;
        
    print_array(array, arr_size_new);
    return exit_code;
}

void get_next_fib(int *first, int *second)
{
    int next_number = *first + *second;
    *first = *second;
    *second = next_number;
}

int start_input_loop(int *array, int arr_size, int *arr_size_new)
{
    int fib_0 = 0;
    int fib_1 = 1;
    int shift = 0;

    for (int i = 0; i < arr_size; i++)
    {
        int result = scanf("%d", &array[i + shift]);
        
        if (result != 1)
            return WRONG_INPUT;

        if (array[i + shift] % 3 == 0)
        {
            shift++;
            array[i + shift] = fib_0;
            get_next_fib(&fib_0, &fib_1);
        }
    }

    *arr_size_new = arr_size + shift;
    return OK;
}

void print_array(int *array, int arr_size)
{
    for (int i = 0; i < arr_size; i++)
        printf("%d ", array[i]);
}
