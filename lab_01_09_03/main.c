#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void add_element_in_array(double **array, double value, int current_size)
{
    double *new_pointer = (double*)malloc(sizeof(double) * (current_size + 1));
    memcpy(new_pointer, *array, sizeof(double)*current_size);
    free(*array);
    new_pointer[current_size] = value;
    *array = new_pointer;
}

double calculate_expression(double *array, int array_size)
{
    double result = 1;

    for (int i = 1; i <= array_size; i++)
    {
        result /= array[i - 1] + i;
    }

    return exp(result);
}

/*int is_zero(double *value)
{
    if (fabs(*value) <= 1e-10)
    {
        *value = 0.0;
        return 1;
    }
    return 0;
}*/

int main()
{
    double value;

    double *array = NULL;
    int array_size = 0;

    while (1)
    {
        if (scanf("%lf", &value) != 1)
        {
            if (array != NULL)
                free(array);
            return -1;
        }

        if (value >= 0) // || is_zero(&value))
        {
            add_element_in_array(&array, value, array_size);
            array_size += 1;
        }
        else
            break;
    }
    
    if (array_size == 0)
    {
        free(array);
        return -2;
    }

    double result = calculate_expression(array, array_size);

    printf("%lf", result);

    free(array);
    return 0;
}