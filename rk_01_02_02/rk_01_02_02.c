#include <stdio.h>

#define MAX_ARRAY_SIZE 100

#define OK 0
#define INVALID_ARRAY_SIZE -1
#define INVALID_ELEMENT -2

int get_array_from_user(int *array, int *array_size)
{
    if (scanf("%d", array_size) != 1)
        return INVALID_ARRAY_SIZE;

    if (array_size <= 0)
        return INVALID_ARRAY_SIZE;

    int *array_end = array + *array_size;

    for (int *ptr = array; ptr != array_end; ptr++)
    {
        if (scanf("%d", ptr) != 1)
            return INVALID_ELEMENT; 
    }

    return OK;
}

void make_ascending_array(int *array, int *array_size)
{
    int *new_ptr = array;
    int *array_end = array + *array_size;

    for (int *old_ptr = array + 1; old_ptr != array_end; old_ptr++)
    {
        if (*old_ptr > *new_ptr)
        {
            *(++new_ptr) = *old_ptr;
        }
    }

    *array_size = (int)(new_ptr - array + 1);
}

void print_array(int *array, int array_size)
{
    int *array_end = array + array_size;

    for (int *ptr = array; ptr != array_end; ptr++)
    {
        printf("%d ", *ptr);
    }
}

int main()
{
    int array[MAX_ARRAY_SIZE];
    int array_size;

    int exit_code = get_array_from_user(array, &array_size);

    if (exit_code != OK)
        return exit_code;

    make_ascending_array(array, &array_size);

    print_array(array, array_size);

    return OK;
}
