#include <stdio.h>

#define ARR_SIZE 10

#define OK 0
#define WRONG_INPUT -1
#define WRONG_ARRAY_SIZE -2

int get_array_from_user(int *arr_begin, int **arr_end);
int count_elements_with_value(int *arr_begin, int *arr_end, int value);
int get_unique_numbers_amount(int *arr_begin, int *arr_end);

int main()
{
    int array[ARR_SIZE];
    int *array_end;
    int exit_code = get_array_from_user(array, &array_end);
    
    if (exit_code != OK)
        return exit_code;

    int unique_numbers_amount = get_unique_numbers_amount(array, array_end);
    printf("%d", unique_numbers_amount);
    return exit_code;
}

int get_array_from_user(int *array, int **array_end)
{
    {
        int arr_size;

        if (scanf("%d", &arr_size) != 1)
            return WRONG_ARRAY_SIZE;

        *array_end = array + arr_size;
    }

    if ((*array_end - array) <= 0 || (*array_end - array) > 10)
        return WRONG_ARRAY_SIZE;

    while (array < *array_end)
    {
        if (scanf("%d", array) != 1)
            return WRONG_INPUT;

        array++;
    }

    return OK;
}

int count_elements_with_value(int *arr_begin, int *arr_end, int value)
{
    int result = 0;

    while (arr_begin != arr_end)
    {
        if (*arr_begin == value)
            result++;

        arr_begin++;
    }

    return result;
}

int get_unique_numbers_amount(int *arr_begin, int *arr_end)
{
    int result = 0;
    int *current_element = arr_begin;

    while (current_element < arr_end)
    {
        if (count_elements_with_value(arr_begin, arr_end, *current_element) == 1)
            result++;

        current_element++;
    }

    return result;
}
