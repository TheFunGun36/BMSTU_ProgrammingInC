#include <stdio.h>
#include "math_module.h"

#define EXIT_INVALID_ARG_AMOUNT -3
#define EXIT_FILE_DOES_NOT_EXIST -4

int main(int argc, char *argv[])
{
    int exit_code = EXIT_SUCCESS;

    if (argc == 2)
    {
        FILE *f = fopen(argv[1], "r");

        if (f)
        {
            float avg, min, max;
            exit_code = calculate_sequence_params(f, &avg, &max, &min);

            if (exit_code == EXIT_SUCCESS)
            {
                float sigma;
                exit_code = calculate_sigma(f, avg, &sigma);

                if (exit_code == EXIT_SUCCESS)
                {
                    printf("%d", (avg - 3 * sigma < min && avg + 3 * sigma > max));
                    printf("\nsigma=%f\nmin=%f\nmax=%f\navg=%f", sigma, min, max, avg);
                }
            }

            fclose(f);
        }
        else
            exit_code = EXIT_FILE_DOES_NOT_EXIST;
    }
    else
        exit_code = EXIT_INVALID_ARG_AMOUNT;

    return exit_code;
}
