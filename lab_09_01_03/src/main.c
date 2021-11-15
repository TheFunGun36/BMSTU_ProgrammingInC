#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "fileio.h"
#include "goods.h"
#include "userio.h"

exit_t check_args(int argc, char *argv[], double *calculated_price);
static int comp(product_t prod, product_t sample);

int main(int argc, char *argv[])
{
    goods_t goods = { 0 };
    double price;

    exit_t exit_code = check_args(argc, argv, &price);

    if (exit_code == EXIT_SUCCESS)
        exit_code = file_read_goods(argv[1], &goods);

    if (exit_code == EXIT_SUCCESS)
    {
        product_t sample = { .price = (int)ceil(price), .name = NULL };
        goods_filter(&goods, sample, comp);
        print_goods(goods);
    }

    goods_free(&goods);
    return exit_code;
}

exit_t check_args(int argc, char *argv[], double *calculated_price)
{
    exit_t exit_code = EXIT_SUCCESS;

    if (argc == 3)
    {
        *calculated_price = atof(argv[2]);

        if (*calculated_price <= 0.0)
            exit_code = EXIT_INVALID_ARGS;
    }
    else
    {
        exit_code = EXIT_INVALID_ARGS;
    }

    return exit_code;
}

int comp(product_t prod, product_t sample)
{
    return prod.price < sample.price;
}
