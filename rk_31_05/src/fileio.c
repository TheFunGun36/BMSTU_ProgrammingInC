#include "fileio.h"
#include <stdio.h>

int fload_field(field_t *state, char *filename)
{
    int exit_code = EXIT_SUCCESS;

    FILE *f = fopen(filename, "rt");

    if (f)
    {
        int res = fscanf(f, "%zu%zu", &state->size_y, &state->size_x);

        if (res != 2)
            exit_code = EXIT_FILE_INV_CONTENT;
        else
            exit_code = field_initialize(state, state->size_x, state->size_y);

        if (exit_code == EXIT_SUCCESS)
        {
            for (int i = 0; exit_code == EXIT_SUCCESS && i < state->size_y; i++)
            {
                for (int j = 0; exit_code == EXIT_SUCCESS && j < state->size_x; j++)
                {
                    int val;
                    res = fscanf(f, "%d", &val);

                    if (res != 1 || (val != 0 && val != 1))
                        exit_code = EXIT_FILE_INV_CONTENT;
                    else
                        state->state[i][j] = val + '0';
                }
            }

            if (exit_code != EXIT_SUCCESS)
                field_free(state);
        }

        fclose(f);
    }
    else
    {
        exit_code = EXIT_FILE_OPEN;
    }

    return exit_code;
}
