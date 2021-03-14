#include <stdio.h>
#include <math.h>

#define ARR_SIZE 10

#define OK 0
#define NO_POSITIVE_ITEMS -1
#define WRONG_INPUT -2

int get_geometric_mean(const int *array, int arr_size, double *result);
int get_array_from_user(int *array, int arr_size);

int main()
{
    int input_array[ARR_SIZE];
    int exit_code = get_array_from_user(input_array, ARR_SIZE);

    if (exit_code != OK)
        return exit_code;

    double result;
    exit_code = get_geometric_mean(input_array, ARR_SIZE, &result);    

    if (exit_code != OK)
        return exit_code;

    printf("%lf", result);

    return exit_code;
}

int get_geometric_mean(const int *array, int arr_size, double *result)
{
    *result = 1.0;
    int counter = 0;

    for (int i = 0; i < arr_size; i++)
    {
        if (array[i] > 0.0)
        {
            *result *= array[i];
            counter++;
        }
    }

    if (counter == 0)
        return NO_POSITIVE_ITEMS;

    *result = pow(*result, 1.0 / counter);
    return OK;
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
