#include "fileio.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STR_INC 8

static exit_t file_read_product(FILE *f, product_t *prod);
static exit_t file_read_string(FILE *f, char **string);
static exit_t file_read_endl(FILE *f);
static exit_t file_count_products(FILE *f, int *result);

exit_t file_read_goods(char *filename, goods_t *goods)
{
    exit_t exit_code = EXIT_SUCCESS;
    FILE *f = fopen(filename, "rt");

    if (f)
    {
        exit_code = file_count_products(f, &goods->amount);
        //int res = fscanf(f, "%d", &goods->amount);
        //if (exit_code == EXIT_SUCCESS)
        //    exit_code = file_read_endl(f);

        if (exit_code == EXIT_SUCCESS)
        {
            if (goods->amount <= 0)
            {
                exit_code = EXIT_FILE_INVALID_CONTENT;
                memset(goods, 0, sizeof(goods_t));
            }
            else
            {
                exit_code = goods_init(goods, goods->amount);
            }
        }

        for (int i = 0; exit_code == EXIT_SUCCESS && i < goods->amount; i++)
            exit_code = file_read_product(f, goods->val + i);

        fclose(f);
    }
    else
    {
        exit_code = EXIT_FILE_OPEN;
    }

    return exit_code;
}

exit_t file_read_product(FILE *f, product_t *prod)
{
    exit_t exit_code = file_read_string(f, &prod->name);

    if (exit_code == EXIT_SUCCESS)
    {
        int res = fscanf(f, "%d", &prod->price);

        if (res != 1)
            exit_code = EXIT_FILE_INVALID_CONTENT;
        else
            exit_code = file_read_endl(f);
    }

    if (exit_code != EXIT_SUCCESS)
    {
        free(prod->name);
        memset(prod, 0, sizeof(product_t));
    }

    return exit_code;
}

exit_t file_read_string(FILE *f, char **str)
{
    exit_t exit_code = EXIT_SUCCESS;
    *str = NULL;

    char read_next = 1;
    char *endl_pos;

    for (int i = STR_INC; exit_code == EXIT_SUCCESS && read_next; i += STR_INC)
    {
        char *new_str = realloc(*str, (i + 1) * sizeof(char));

        if (!new_str)
        {
            exit_code = EXIT_NO_MEMORY;
        }
        else 
        {
            *str = new_str;

            if (!fgets(*str + i - STR_INC, STR_INC + 1, f))
                exit_code = EXIT_FILE_INVALID_CONTENT;
        }

        if (exit_code == EXIT_SUCCESS)
        {
            endl_pos = strchr(*str, '\n');

            if (endl_pos)
            {
                *endl_pos = '\0';

                if (endl_pos - *str - 1 >= 0 && *(endl_pos - 1) == '\r')
                    *(--endl_pos) = '\0';

                read_next = 0;

                if (endl_pos - *str <= 0)
                    exit_code = EXIT_FILE_INVALID_CONTENT;
            }
        }
    }
    
    if (exit_code != EXIT_SUCCESS)
    {
        free(*str);
        *str = NULL;
    }

    return exit_code;
}

exit_t file_read_endl(FILE *f)
{
    char endl;
    int res = fscanf(f, "%c", &endl);

    if (res == 1 && endl == '\r')
        res = fscanf(f, "%c", &endl);

    return (res == 1 && endl == '\n') ? (EXIT_SUCCESS) : (EXIT_FILE_INVALID_CONTENT);
}

exit_t file_count_products(FILE *f, int *result)
{
    exit_t exit_code = EXIT_SUCCESS;
    product_t product;

    *result = 0;

    while (exit_code == EXIT_SUCCESS)
    {
        exit_code = file_read_product(f, &product);
        (*result)++;
    }

    (*result)--;

    rewind(f);

    return EXIT_SUCCESS;
}
