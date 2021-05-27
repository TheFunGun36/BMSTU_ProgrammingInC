#include <math.h>
#include "math_module.h"

int calculate_sequence_params(FILE *f, float *avg, float *max, float *min)
{
    int exit_code = EXIT_SUCCESS;
    float current_number;
    int read_result = fscanf(f, "%f", &current_number);

    if (read_result == 1)
    {
        float sum = 0;
        int numbers_amount = 0;

        *max = current_number;
        *min = current_number;

        do
        {
            if (current_number > *max)
                *max = current_number;
            else if (current_number < *min)
                *min = current_number;

            sum += current_number;
            numbers_amount++;

            read_result = fscanf(f, "%f", &current_number);
        }
        while (read_result == 1);

        if (read_result == EOF)
            *avg = sum / numbers_amount;
        else
            exit_code = EXIT_INVALID_ELEMENT;
    }
    else
    {
        exit_code = EXIT_EMPTY_FILE;
    }

    fseek(f, 0, SEEK_SET);
    return exit_code;
}

int calculate_sigma(FILE *f, float avg, float *sigma)
{
    int exit_code = EXIT_SUCCESS;
    float current_number;
    int read_result = fscanf(f, "%f", &current_number);

    if (read_result == 1)
    {
        float sum = 0;
        int numbers_amount = 0;

        do
        {
            sum += (avg - current_number) * (avg - current_number);
            numbers_amount++;
            read_result = fscanf(f, "%f", &current_number);
        }
        while (read_result == 1);

        if (read_result == EOF)
            *sigma = sqrt(sum / numbers_amount);
        else
            exit_code = EXIT_INVALID_ELEMENT;
    }
    else
    {
        exit_code = EXIT_EMPTY_FILE;
    }

    fseek(f, 0, SEEK_SET);
    return exit_code;
}
