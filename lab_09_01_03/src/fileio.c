#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "fileio.h"

#define EOF_NOT_FOUND 0
#define EOF_FOUND 1
#define EOF_SEARCHING 2

#define STR_INC 4

static int file_read_number(unsigned int *number, FILE *f);
static int seek_eof(FILE *f);
static int file_read_product(FILE *f, product_t *prod);
static int file_read_string(FILE *f, char **str);
static int file_read_endl(FILE *f);

int file_read_endl(FILE *f)
{
    const char *space_symbols = "\r\n\t\v\f";
    int result = EXIT_SUCCESS;

    char c;

    do
    {
        c = fgetc(f);

        if (c == EOF)
            result = EOF;
        else if (!strchr(space_symbols, c))
            result = EXIT_LINE_NOT_READ;
    } while (result == EXIT_SUCCESS && c != '\n');

    return result;
}

int file_read_number(unsigned int *number, FILE *f)
{
    int exit_code = EXIT_SUCCESS;
    long long number_signed;
    int result = fscanf(f, "%lld", &number_signed);

    if (result == 1)
    {
        if (number_signed < 0 || number_signed > INT32_MAX)
            exit_code = EXIT_INVALID_NUMBER;
        else
            exit_code = file_read_endl(f);
    }
    else
    {
        exit_code = EXIT_INVALID_NUMBER;
    }

    if (exit_code == EXIT_SUCCESS || exit_code == EOF)
        *number = number_signed;

    return exit_code;
}

int seek_eof(FILE *f)
{
    const char *space_symbols = "\r\n\t\v\f";
    int result = EOF_SEARCHING;

    while (result == EOF_SEARCHING)
    {
        char c = fgetc(f);

        if (c == EOF)
            result = EOF_FOUND;
        else if (strchr(space_symbols, c))
            result = EOF_NOT_FOUND;
    }

    return result;
}

int read_product_arr(product_t **product_arr, unsigned int *product_arr_size, char *filename)
{
    int exit_code = EXIT_SUCCESS;
    FILE *f = fopen(filename, "rt");

    if (f)
    {
        exit_code = file_read_number(product_arr_size, f);
        
        if (exit_code == EXIT_SUCCESS && *product_arr_size > 0)
        {
            *product_arr = calloc(*product_arr_size, sizeof(product_t));

            for (unsigned int i = 0; i < *product_arr_size && exit_code == EXIT_SUCCESS; i++)
                exit_code = file_read_product(f, *product_arr + i);

            if (seek_eof(f) == EOF_NOT_FOUND)
                exit_code = EXIT_INVALID_PRODUCTS_AMOUNT;

            if (exit_code != EXIT_SUCCESS)
            {
                for (int i = 0; i < *product_arr_size; i++)
                    free((*product_arr)[i].name);
                free(*product_arr);
                *product_arr = NULL;
            }
        }
        else
        {
            exit_code = EXIT_INVALID_PRODUCTS_AMOUNT;
        }        

        fclose(f);
    }
    else
    {
        exit_code = EXIT_FILE_NOT_OPENED;
    }
    
    return exit_code;
}

int file_read_product(FILE *f, product_t *prod)
{
    int exit_code = file_read_string(f, &prod->name);

    if (exit_code == EXIT_SUCCESS)
    {
        exit_code = file_read_number(&prod->price, f);

        if (exit_code == EOF)
            exit_code = EXIT_SUCCESS;
    }

    if (exit_code != EXIT_SUCCESS)
    {
        free(prod->name);
        memset(prod, 0, sizeof(product_t));
    }

    return exit_code;
}

int file_read_string(FILE *f, char **str)
{
    int exit_code = EXIT_SUCCESS;
    *str = NULL;

    char read_next = 1;
    char *endl_pos;

    for (int i = STR_INC; exit_code == EXIT_SUCCESS && read_next; i += STR_INC)
    {
        char *new_str;
        
        if (str)
            new_str = realloc(*str, (i + 1) * sizeof(char));
        else
            new_str = malloc((i + 1) * sizeof(char));

        if (!new_str)
        {
            exit_code = EXIT_NO_MEMORY;
        }
        else 
        {
            *str = new_str;

            if (!fgets(*str + i - STR_INC, STR_INC + 1, f))
                exit_code = EXIT_LINE_NOT_READ;
        }

        if (exit_code == EXIT_SUCCESS)
        {
            endl_pos = strchr(*str, '\n');

            if (endl_pos)
            {
                if (endl_pos - *str - 1 >= 0 && *(endl_pos - 1) == '\r')
                    endl_pos--;
                *endl_pos = '\0';

                read_next = 0;

                if (endl_pos - *str <= 0)
                    exit_code = EXIT_LINE_NOT_READ;
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
