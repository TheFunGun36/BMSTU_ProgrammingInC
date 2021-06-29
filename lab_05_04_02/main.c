#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "goods.h"
#include "fileio.h"

#define EXIT_INVALID_ARGS 53

int sort_file(char *filename_in, char *filename_out)
{
    int exit_code;
    product_t goods[GOODS_MAX_AMOUNT] = { 0 };
    int goods_amount = 0;

    exit_code = goods_fread(filename_in, goods, &goods_amount);

    if (exit_code == EXIT_SUCCESS && goods_amount <= 1)
        exit_code = ERR_NOTHING_TO_SORT;

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
    product_t goods[GOODS_MAX_AMOUNT] = { 0 };
    int goods_amount = 0;

    if (strlen(substr) > PRODUCT_NAME_LENGTH - 2)
        return ERR_LONG_STRING;

    exit_code = goods_fread(filename, goods, &goods_amount);

    if (exit_code == EXIT_SUCCESS)
    {
        exit_code = goods_print(goods, goods_amount, substr);
    }

    return exit_code;
}

int add_to_file(char *filename)
{
    product_t goods[GOODS_MAX_AMOUNT] = { 0 };
    product_t new_product = { 0 };
    int goods_amount = 0;

    int exit_code = goods_fread(filename, goods, &goods_amount);

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

int is_args_valid(int argc, char *argv[])
{
    int result = 0;

    if (argc == 3)
    {
        if (argv[1][0] == 'a' && argv[1][1] == 't' && argv[1][2] == '\0')
            return 1;
    }
    else if (argc == 4)
    {
        if ((argv[1][0] == 's' || argv[1][0] == 'f') && argv[1][1] == 't' && argv[1][2] == '\0')
            return 1;
    }

    return result;
}

int main(int argc, char *argv[])
{
    int exit_code = EXIT_SUCCESS;

    if (!is_args_valid(argc, argv))
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
