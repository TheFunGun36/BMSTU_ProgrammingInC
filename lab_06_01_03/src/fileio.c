#include <stdio.h>
#include <string.h>
#include "fileio.h"

#define EOF_NOT_FOUND 0
#define EOF_FOUND 1
#define EOF_SEARCHING 2

int validate_string(char *str)
{
    int result = 0;
    char *name_end = strchr(str, '\r');

    if (!name_end)
    {
        name_end = strchr(str, '\n');
        
        if (name_end)
            *name_end = '\0';
        else
            result = EXIT_LONG_INPUT_STRING;
    }
    else
    {
        *name_end = '\0';
    }

    if (str >= name_end)
        result = EXIT_EMPTY_INPUT_STRING;

    return result;
}

int file_read_line(char *str, FILE *f)
{
    int exit_code = EXIT_SUCCESS;
    char str_tmp[MAX_PRODUCT_NAME_SIZE + 2];
    char *result = fgets(str_tmp, MAX_PRODUCT_NAME_SIZE + 2, f);

    if (result)
    {
        exit_code = validate_string(str_tmp);

        if (exit_code == EXIT_SUCCESS)
            strcpy(str, str_tmp);
    }
    else
        exit_code = EXIT_LINE_NOT_READ;

    return exit_code;
}

int file_read_number(unsigned int *number, FILE *f)
{
    int exit_code = EXIT_SUCCESS;
    int number_signed;
    int result = fscanf(f, "%d", &number_signed);

    if (result == 1)
    {
        if (number_signed < 0)
            exit_code = EXIT_INVALID_NUMBER;
        else
        {
            char s = fgetc(f);

            if (s == '\r')
            {
                s = fgetc(f);
                if (s != '\n')
                    exit_code = EXIT_INVALID_NUMBER;
            }
            else if (s != EOF && s != '\n')
                exit_code = EXIT_INVALID_NUMBER;
        }
    }
    else
        exit_code = EXIT_INVALID_NUMBER;

    if (exit_code == EXIT_SUCCESS)
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

int read_product_arr(product_t *product_arr, unsigned int *product_arr_size, char *filename)
{
    int exit_code = EXIT_SUCCESS;
    FILE *f = fopen(filename, "rb");

    if (f)
    {
        unsigned int products_amount;
        exit_code = file_read_number(&products_amount, f);
        
        if (exit_code == EXIT_SUCCESS && 0 < products_amount && products_amount <= MAX_PRODUCTS_AMOUNT)
        {
            for (unsigned int i = 0; i < products_amount && exit_code == EXIT_SUCCESS; i++)
            {
                product_t *current_product = product_arr + i;

                exit_code = file_read_line(current_product->name, f);

                if (exit_code == EXIT_SUCCESS)
                    exit_code = file_read_number(&current_product->price, f);
            }
            
            *product_arr_size = products_amount;

            if (seek_eof(f) == EOF_NOT_FOUND)
                exit_code = EXIT_INVALID_PRODUCTS_AMOUNT;
        }
        else
            exit_code = EXIT_INVALID_PRODUCTS_AMOUNT;
        

        fclose(f);
    }
    else
        exit_code = EXIT_FILE_NOT_OPENED;
    
    return exit_code;
}
