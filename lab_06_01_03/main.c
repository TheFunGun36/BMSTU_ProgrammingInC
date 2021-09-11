#include <stdlib.h>
#include <stdio.h>
#include "fileio.h"
#include "product.h"

#define EXIT_INVALID_MAX_PRICE -7
#define EXIT_EMPTY_RESULT_ARRAY -8

int check_args(int argc, char *argv[], double *calculated_price)
{
    int exit_code = EXIT_SUCCESS;

    if (argc == 3)
    {
        *calculated_price = atof(argv[2]);

        if (*calculated_price <= 0.0)
            exit_code = EXIT_INVALID_MAX_PRICE;
    }

    return exit_code;
}

void print_product_array(product_t *product_arr, unsigned int product_arr_size)
{
    for (int i = 0; i < product_arr_size; i++)
    {
        printf("%s\n%u\n", product_arr[i].name, product_arr[i].price);
    }
}

int main(int argc, char *argv[])
{
    double max_price;
    int exit_code = check_args(argc, argv, &max_price);

    if (exit_code == EXIT_SUCCESS)
    {
        product_t product_arr[MAX_PRODUCTS_AMOUNT];
        unsigned int product_arr_size;
        exit_code = read_product_arr(product_arr, &product_arr_size, argv[1]);

        if (exit_code == EXIT_SUCCESS)
        { 
            filter_product_array(product_arr, &product_arr_size, max_price);

            print_product_array(product_arr, product_arr_size);
        }
    }

    return exit_code;
}
