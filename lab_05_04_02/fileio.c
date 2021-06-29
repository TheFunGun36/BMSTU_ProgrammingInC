#include <string.h>
#include "fileio.h"

int goods_print(product_t goods[], int goods_amount, char *name_endl_mask)
{
    unsigned int mask_len = strlen(name_endl_mask);
    int exit_code = ERR_NOTHING_TO_PRINT;

    for (int i = 0; i < goods_amount; i++)
    {
        int is_printed = 0;

        if (strlen(goods[i].name) >= mask_len)
        {
            char *ptr = strchr(goods[i].name, '\0') - mask_len;
            is_printed = strcmp(name_endl_mask, ptr) == 0;
        }

        if (is_printed)
        {
            exit_code = EXIT_SUCCESS;
            printf("%s\n", goods[i].name);
            printf("%s\n", goods[i].manufacturer);
            printf("%u\n", goods[i].price);
            printf("%u\n", goods[i].amount);
        }
    }

    return exit_code;
}

int readline(FILE *f, char *str, int max_str_size)
{
    int exit_code = EXIT_SUCCESS;

    fgets(str, max_str_size, f);

    int len = strlen(str);

    if (len >= 1 && (str[len - 1] == '\r' || str[len - 1] == '\n'))
    {
        str[--len] = '\0';

        if (len >= 1 && (str[len - 1] == '\r' || str[len - 1] == '\n'))
        {
            str[--len] = '\0';
        }
    }

    if (len <= 0)
        exit_code = ERR_EMPTY_STRING;
    else if (len > max_str_size - 2)
        exit_code = ERR_LONG_STRING;

    return exit_code;
}

int product_fread(FILE *f, product_t *product)
{
    int exit_code = readline(f, product->name, PRODUCT_NAME_LENGTH);

    if (feof(f) || ferror(f))
        exit_code = ERR_NO_ACCESS;

    if (exit_code == EXIT_SUCCESS)
    {
        exit_code = readline(f, product->manufacturer, PRODUCT_MAN_LENGTH);

        if (feof(f) || ferror(f))
            exit_code = ERR_INCOMPLETE_STRUCT;
    }

    if (exit_code == EXIT_SUCCESS)
    {
        int result = fscanf(f, "%u", &product->price);

        if (result == 1)
            result = fscanf(f, "%u", &product->amount);

        if (result != 1)
            exit_code = ERR_INCOMPLETE_STRUCT;

        char trash[3] = { 0 };
        fgets(trash, 3, f);
    }

    return exit_code;
}

int goods_fread(char *filename, product_t goods[], int *goods_amount)
{
    int exit_code = EXIT_SUCCESS;
    FILE *f = fopen(filename, "r");

    if (f)
    {
        (*goods_amount) = 0;

        do
        {
            exit_code = product_fread(f, goods + *goods_amount);

            if (exit_code == EXIT_SUCCESS)
                (*goods_amount)++;
        }
        while (!(feof(f) || ferror(f) || exit_code != EXIT_SUCCESS || *goods_amount >= GOODS_MAX_AMOUNT - 1));

        if (!feof(f))
        {
            exit_code = ERR_NO_ACCESS;
        }
        else if (exit_code == ERR_NO_ACCESS)
        {
            exit_code = EXIT_SUCCESS;
        }

        fclose(f);
    }
    else
        return ERR_NO_ACCESS;

    return exit_code;
}

int goods_fwrite(char *filename, product_t goods[], int goods_amount)
{
    int exit_code = EXIT_SUCCESS;

    FILE *f = fopen(filename, "w");

    if (f)
    {
        for (int i = 0; i < goods_amount; i++)
        {
            int res = fprintf(f, "%s\n", goods[i].name);

            if (res <= 0)
            {
                exit_code = ERR_NO_ACCESS;
                break;
            }

            res = fprintf(f, "%s\n", goods[i].manufacturer);

            if (res <= 0)
            {
                exit_code = ERR_NO_ACCESS;
                break;
            }

            res = fprintf(f, "%u\n", goods[i].price);

            if (res <= 0)
            {
                exit_code = ERR_NO_ACCESS;
                break;
            }

            res = fprintf(f, "%u\n", goods[i].amount);

            if (res <= 0)
            {
                exit_code = ERR_NO_ACCESS;
                break;
            }
        }

        fclose(f);
    }
    else
        return ERR_NO_ACCESS;

    return exit_code;
}
