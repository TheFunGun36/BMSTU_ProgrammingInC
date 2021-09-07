#include "product.h"

void filter_product_array(product_t *product_arr, unsigned int *array_size, double max_price)
{
    product_t *new_array_ptr = product_arr;
    product_t *old_array_ptr = product_arr;

    while (old_array_ptr - product_arr < *array_size)
    {
        if (old_array_ptr->price < max_price)
        {
            *new_array_ptr = *old_array_ptr;
            new_array_ptr++;
        }

        old_array_ptr++;
    }

    *array_size = new_array_ptr - product_arr;
}