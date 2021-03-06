#include <stdio.h>

#define ARR_SIZE_MAX 11

#define OK 0
#define NO_ELEMENTS -1
#define ARRAY_OVERFLOW 100

int get_array_from_user(int *array, int *arr_size);
void insertion_sort(int *array, int arr_size);
void print_array(int *array, int arr_size);

int main()
{
    int array[ARR_SIZE_MAX];
    int array_size = ARR_SIZE_MAX;
    int exit_code = get_array_from_user(array, &array_size);

    if (exit_code != OK && exit_code != ARRAY_OVERFLOW)
        return exit_code;

    insertion_sort(array, array_size);
    print_array(array, array_size);
    return exit_code;
}

int get_array_from_user(int *array, int *array_size)
{
    int result = 1;
    int i;
    for (i = 0; i < *array_size && result == 1; i++)
    {
        result = scanf("%d", &array[i]);
    }

    int return_code;

    if (i > 10 && result == 1)
    {
        *array_size = 10;
        return_code = ARRAY_OVERFLOW;
    }
    else if (i <= 1)
    {
        return_code = NO_ELEMENTS;
    }
    else
    {
        *array_size = i - 1;
        return_code = OK;
    }

    return return_code;
}

void insertion_sort(int *array, int array_size)
{
    for (int i = 1; i < array_size; i++)
    {
        int current_value = array[i];
        int shift_from = 0;

        while (array[shift_from] < current_value && shift_from < i)
            shift_from++;

        for (int j = i; j > shift_from; j--)
            array[j] = array[j - 1];

        array[shift_from] = current_value;
    }
}

void print_array(int *array, int array_size)
{
    for (int i = 0; i < array_size; i++)
        printf("%d ", array[i]);
}