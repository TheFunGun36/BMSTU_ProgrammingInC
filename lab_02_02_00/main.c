#include <stdio.h>

#define ARR_SIZE 10

#define OK 0
#define WRONG_INPUT -1
#define WRONG_ARRAY_SIZE -2

int get_array_from_user(int *array, int *arr_size);
double get_arithmetic_mean(int *array, int arr_size);
void reform_array(int *array, int *arr_size);
void print_array(int *array, int arr_size);

int main()
{
    int array[ARR_SIZE];
    int array_size;
    int exit_code = get_array_from_user(array, &array_size);

    if (exit_code != OK)
        return exit_code;

    reform_array(array, &array_size);

    print_array(array, array_size);

    return exit_code;
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

double get_arithmetic_mean(int *array, int arr_size)
{
    double result = 0.0;

    for (int i = 0; i < arr_size; i++)
        result += array[i];

    return result / arr_size;
}

void reform_array(int *array, int *arr_size)
{
    double arithmetic_mean = get_arithmetic_mean(array, *arr_size);
    int new_size = 0;

    for (int i = 0; i < *arr_size; i++)
    {
        if (array[i] > arithmetic_mean)
        {
            array[new_size] = array[i];
            new_size++;
        }
    }

    *arr_size = new_size;
}

void print_array(int *array, int arr_size)
{
    for (int i = 0; i < arr_size; i++)
        printf("%d ", array[i]);
}
