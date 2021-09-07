#ifndef PRODUCT_H
#define PRODUCT_H

#define MAX_PRODUCT_NAME_SIZE 25

typedef struct product_t
{
    char name[MAX_PRODUCT_NAME_SIZE];
    unsigned int price;
} product_t;

void filter_product_array(product_t *product_arr, unsigned int *array_size, double max_price);

#endif