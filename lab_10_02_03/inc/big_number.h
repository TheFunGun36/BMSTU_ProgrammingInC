#ifndef BIG_NUMBER_H
#define BIG_NUMBER_H

#include "list.h"
#include "dynamic_array.h"

node_t *bign_from_int(int value, int_darr_t *arr, int *exit_code);
node_t *bign_multiply(node_t **a, node_t **b);
node_t *bign_divide(node_t **a, node_t **b, int *found_negatives);
void bign_square(node_t *number);
void bign_print(node_t *number);

#endif
