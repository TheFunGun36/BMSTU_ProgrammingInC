#include <stdio.h>

#define ARR_SIZE 10

#define OK 0
#define WRONG_INPUT -1

int get_array_from_user(int *array, int arr_size);
double get_arithmetic_mean(int *array, int arr_size);
void form_new_array(int *source, int src_size, int *destination, int *dest_size);
void print_array(int *array, int arr_size);

int main()
{
    int input_array[ARR_SIZE];
    int exit_code = get_array_from_user(input_array, ARR_SIZE);

    if (exit_code != OK)
        return exit_code;

    int result_array[ARR_SIZE];
    int new_array_size;

    form_new_array(input_array, ARR_SIZE, result_array, &new_array_size);

    print_array(result_array, new_array_size);

    return 0;
}

int get_array_from_user(int *array, int arr_size)
{
    for (int i = 0; i < arr_size; i++)
    {
        if (scanf("%d", &array[i]) != 1)
            return WRONG_INPUT;
    }

    return OK;
}

double get_arithmetic_mean(int *array, int arr_size)
{
    double result = 0.0;

    for (int i = 0; i < arr_size; i++)
        result += array[i];

    return result / arr_size;
}

void form_new_array(int *source, int src_size, int *destination, int *dest_size)
{
    double arithmetic_mean = get_arithmetic_mean(source, src_size);
    *dest_size = 0;

    for (int i = 0; i < src_size; i++)
    {
        if (source[i] > arithmetic_mean)
        {
            (*dest_size)++;
            *destination = source[i];
            destination++;
        }
    }
}

void print_array(int *array, int arr_size)
{
    for (int i = 0; i < arr_size; i++)
        printf("%d ", array[i]);
}