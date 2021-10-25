#include "field.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static char is_cell_alive(const field_t *state, int pos_x, int pos_y);
static char get_cell_state(const field_t *state, int pos_x, int pos_y);

int field_gen_next_state(const field_t *current, field_t *new)
{
    int exit_code = field_initialize(new, current->size_x, current->size_y);

    if (exit_code == EXIT_SUCCESS)
    {
        for (int i = 0; i < current->size_y; i++)
        {
            for (int j = 0; j < current->size_x; j++)
            {
                new->state[i][j] = is_cell_alive(current, j, i) ? '1' : '0';
            }
        }
    }

    return exit_code;
}

int field_compare(const field_t *first, const field_t *second)
{
    int diff = 0;

    for (int i = 0; i < first->size_y; i++)
        for (int j = 0; j < first->size_x; j++)
            diff += first->state[i][j] != second->state[i][j];

    return diff;
}

int field_initialize(field_t *field, size_t size_x, size_t size_y)
{
    field->size_x = size_x;
    field->size_y = size_y;

    field->state = (char**)calloc(size_y, sizeof(char*));

    int exit_code = EXIT_SUCCESS;

    if (!field->state)
    {
        exit_code = EXIT_NO_MEMORY;
    }
    else
    {
        for (int i = 0; exit_code == EXIT_SUCCESS && i < size_y; i++)
        {
            field->state[i] = (char*)calloc(size_x, sizeof(char));

            if (!field->state[i])
                exit_code = EXIT_NO_MEMORY;
        }
    }

    if (exit_code != EXIT_SUCCESS)
        field_free(field);

    return exit_code;
}

void field_print(const field_t *state)
{
    for (int i = 0; i < state->size_y; i++)
    {
        for (int j = 0; j < state->size_x; j++)
           printf("%c", state->state[i][j]);

        printf("\n");
    }
}

char field_is_dead(const field_t *state)
{
    char found_alive = 0;

    for (int i = 0; !found_alive && i < state->size_y; i++)
        for (int j = 0; !found_alive && j < state->size_x; j++)
            found_alive = state->state[i][j] == '1';

    return !found_alive;
}

void field_free(field_t *state)
{
    for (int i = 0; i < state->size_y; i++)
        free(state->state[i]);

    free(state->state);

    memset(state, 0, sizeof(field_t));
}

char is_cell_alive(const field_t *state, int pos_x, int pos_y)
{
    int alives_around = 0;

    for (int i = pos_y - 1; i <= pos_y + 1; i++)
        for (int j = pos_x - 1; j <= pos_x + 1; j++)
            alives_around += get_cell_state(state, j, i);

    return alives_around == 3 || (alives_around == 2 && state->state[pos_y][pos_x]);
}

char get_cell_state(const field_t *state, int pos_x, int pos_y)
{
    while (pos_x < 0)
        pos_x += state->size_x;
    while (pos_x >= state->size_x)
        pos_x -= state->size_x;

    while (pos_y < 0)
        pos_y += state->size_y;
    while (pos_y >= state->size_y)
        pos_y -= state->size_y;

    return state->state[pos_y][pos_x] == '1';
}
