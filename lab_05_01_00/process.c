#include "process.h"

#define EXIT_SUCCESS 0
#define EXIT_EMPTY_INPUT -1
#define EXIT_NO_ANSWER -2

int process(FILE *f)
{
    int exit_code = EXIT_SUCCESS;

    int is_prev_neg = 0;
    int best_result = -1;

    int current_number;
    int scan_result = fscanf(f, "%d", &current_number);

    if (scan_result == 1)
    {
        do
        {
            if (is_prev_neg && current_number > best_result)
                best_result = current_number;

            is_prev_neg = current_number < 0;

            scan_result = fscanf(f, "%d", &current_number);
        }
        while (scan_result == 1);

        if (best_result < 0)
            exit_code = EXIT_NO_ANSWER;
        else
            printf("%d", best_result);
    }
    else
    {
        exit_code = EXIT_EMPTY_INPUT;
    }

    return exit_code;
}
