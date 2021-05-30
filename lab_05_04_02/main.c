#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "goods.h"
#include "fileio.h"

#define EXIT_INVALID_ARGS 53
#define GOODS_MAX_AMOUNT 100

int sort_file(char *filename_in, char *filename_out)
{
    int exit_code;
    product_t goods[GOODS_MAX_AMOUNT];
    int goods_amount;

    exit_code = goods_fread(filename_in, goods, &goods_amount);

    if (exit_code == EXIT_SUCCESS)
    {
        goods_sort_price_descend(goods, goods_amount);
        exit_code = goods_fwrite(filename_out, goods, goods_amount);
    }

    return exit_code;
}

int print_file(char *filename, char *substr)
{
    int exit_code;
    product_t goods[GOODS_MAX_AMOUNT];
    int goods_amount;

    if (strlen(substr) > PRODUCT_NAME_LENGTH - 2)
        return ERR_LONG_STRING;

    exit_code = goods_fread(filename, goods, &goods_amount);

    if (exit_code == EXIT_SUCCESS)
    {
        goods_print(goods, goods_amount, substr);
    }

    return exit_code;
}

int add_to_file(char *filename)
{
    int exit_code;
    product_t goods[GOODS_MAX_AMOUNT];
    product_t new_product;
    int goods_amount;

    exit_code = goods_fread(filename, goods, &goods_amount);

    if (exit_code == EXIT_SUCCESS)
    {
        exit_code = product_fread(stdin, &new_product);
    }

    if (exit_code == EXIT_SUCCESS)
    {
        goods_insert(goods, &goods_amount, new_product);
        exit_code = goods_fwrite(filename, goods, goods_amount);
    }

    return exit_code;
}

int main(int argc, char *argv[])
{
    int exit_code = EXIT_SUCCESS;

    if (!((argc == 3 && strcmp(argv[1], "at") == 0) || (argc == 4 && (strcmp(argv[1], "st") == 0 || strcmp(argv[1], "ft") == 0))))
        return EXIT_INVALID_ARGS;

    switch (argv[1][0])
    {
        case 's':
            exit_code = sort_file(argv[2], argv[3]);
            break;
        case 'f':
            exit_code = print_file(argv[2], argv[3]);
            break;
        case 'a':
            exit_code = add_to_file(argv[2]);
            break;
        default:
            exit_code = EXIT_INVALID_ARGS;
    }

    return exit_code;
}
