#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "fileio.h"
#include "goods.h"
#include "userio.h"

static exit_t validate_args(int argc, char *argv[], double *converted_price);
static int comp(product_t prod, product_t sample);

int main(int argc, char *argv[])
{
    goods_t goods = { 0 };
    double price;

    exit_t exit_code = validate_args(argc, argv, &price);

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

exit_t validate_args(int argc, char *argv[], double *converted_price)
{
    exit_t exit_code = EXIT_SUCCESS;

    if (argc != 3)
    {
        exit_code = EXIT_INVALID_ARGS;
    }
    else
    {
        char *endptr;
        *converted_price = strtod(argv[2], &endptr);

        if (endptr != strrchr(argv[2], '\0'))
            exit_code = EXIT_INVALID_ARGS;
    }

    return exit_code;
}

int comp(product_t prod, product_t sample)
{
    return prod.price < sample.price;
}
