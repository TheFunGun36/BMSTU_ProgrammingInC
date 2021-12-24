#ifndef PRODUCT_H
#define PRODUCT_H

typedef struct product_t
{
    char *name;
    unsigned int price;
} product_t;

void filter_product_array(product_t *product_arr, unsigned int *array_size, double max_price);

#endif
