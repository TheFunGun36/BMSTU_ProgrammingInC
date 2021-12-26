#ifndef FIELD_H
#define FIELD_H

#include <stdlib.h>

#define EXIT_SUCCESS 0
#define EXIT_NO_MEMORY 1

typedef struct
{
    size_t size_x, size_y;
    char **state;
} field_t;

int field_gen_next_state(const field_t *current, field_t *new);
int field_compare(const field_t *first, const field_t *second);
int field_initialize(field_t *field, size_t size_x, size_t size_y);
void field_print(const field_t *state);
char field_is_dead(const field_t *state);
void field_free(field_t *state);

#endif
