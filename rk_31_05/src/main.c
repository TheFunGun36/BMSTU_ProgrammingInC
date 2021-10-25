#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileio.h"

#define EXIT_SUCCESS 0
#define EXIT_INV_ARGS 4

char is_args_valid(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    int exit_code = EXIT_SUCCESS;
    char is_game_end = 0;

    field_t state;
    exit_code = fload_field(&state, argv[1]);

    if (exit_code == EXIT_SUCCESS)
    {
        int current_step = 1;
        int max_step = atoi(argv[1]);
        printf("Loaded from file:\n");
        field_print(&state);
        field_t next;

        while (!is_game_end)
        {
            exit_code = field_gen_next_state(&state, &next);

            if (exit_code == EXIT_SUCCESS)
            {
                printf("Step %d:\n", current_step++);
                field_print(&next);

                is_game_end = field_compare(&state, &next) == 0 || field_is_dead(&state);
                if (!is_game_end)
                    is_game_end = max_step > 0 && current_step >= max_step;

                field_free(&state);
                state = next;
            }
        }

        if (exit_code == EXIT_SUCCESS)
            printf("Game ended\n");

        field_free(&state);
    }

    return exit_code;
}

char is_args_valid(int argc, char *argv[])
{
    return argc == 3 && atoi(argv[2]);
}
