#include <stdio.h>
#include <math.h>

#define EXIT_OK 0
#define EXIT_ERR_INVALID_INPUT -1
#define EXIT_ERR_NO_INPUT -2

int is_zero(double *value);
int start_input_loop(double *result);

int main()
{
    double exp_argument = 1;
    
    int exit_code = start_input_loop(&exp_argument);

    if (exit_code != EXIT_OK)
        return exit_code;

    printf("%lf", exp(exp_argument));

    return EXIT_OK;
}

int start_input_loop(double *result)
{
    *result = 1.0;
    double current_value = 1.0;
    int i;

    for (i = 1; current_value >= 0 || is_zero(&current_value); i++)
    {
        if (scanf("%lf", &current_value) != 1)
            return EXIT_ERR_INVALID_INPUT;

        if (current_value >= 0 || is_zero(&current_value))
            *result /= current_value + i;
        else
            break;
    }

    if (i == 1)
        return EXIT_ERR_NO_INPUT;

    return EXIT_OK;
}

int is_zero(double *value)
{
    if (fabs(*value) <= 1e-6)
    {
        *value = 0.0;
        return 1;
    }

    return 0;
}
