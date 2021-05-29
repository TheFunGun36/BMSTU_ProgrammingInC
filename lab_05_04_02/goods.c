#include <string.h>
#include <stdio.h>
#include "goods.h"

#define DEBUG

int is_valid_product(Product product)
{
    int result = strnlen(product.name, PRODUCT_NAME_LENGTH) >= PRODUCT_NAME_LENGTH;
    result |= strnlen(product.manufacturer, PRODUCT_MAN_LENGTH) >= PRODUCT_MAN_LENGTH;
    return result;
}

void goods_sort_price_descend(Product goods[], int goods_amount)
{
    for (int i = 1; i < goods_amount; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (goods[j].price < goods[i].price || (goods[j].price == goods[i].price && goods[j].amount < goods[i].amount))
            {
                Product tmp = goods[j];

                for (int k = j; k < i; k++)
                {
                    goods[k] = goods[k + 1];
                }

                goods[i] = tmp;

                break;
            }
        }
    }
}

void goods_print(Product goods[], int goods_amount, char *name_endl_mask)
{
    for (int i = 0; i < goods_amount; i++)
    {
        char *ptr = goods[i].name + PRODUCT_NAME_LENGTH - strnlen(name_endl_mask, PRODUCT_NAME_LENGTH) - 1;
        int is_printed = strcmp(name_endl_mask, ptr);
#ifdef DEBUG
        if (is_printed)
            printf("[PRINTED] ");
        printf("%d:\n", i + 1);
        printf("\tname: %s\t", goods[i].name);
        printf("\tmanufacturer=%s\t", goods[i].manufacturer);
        printf("\tprice=%ud\t", goods[i].price);
        printf("\tamount=%ud\n\n", goods[i].amount);
#else
        if (is_printed)
        {
            printf("%s\n", goods[i].name);
            printf("%s\n", goods[i].manufacturer);
            printf("%ud\n", goods[i].price);
            printf("%ud\n", goods[i].amount);
        }
#endif
    }
}

void goods_insert(Product goods[], int *goods_amount, Product new_product)
{
    for (int i = 0; i < *goods_amount; i++)
    {
        if (goods[i].price < new_product.price || (goods[i].price == new_product.price && goods[i].amount < new_product.amount))
        {
            for (int j = *goods_amount; j >= i; j--)
            {
                goods[j] = goods[j - 1];
            }

            goods[i] = new_product;
            (*goods_amount)++;
            break;
        }
    }
}

int goods_fread(char *filename, Product goods[], int *goods_amount)
{
    FILE *f = fopen(filename, "r");

    int exit_code = SUCCESS;

    if (f)
    {
        (*goods_amount) = 0;

        do
        {
            fgets(goods[*goods_amount].name, PRODUCT_NAME_LENGTH, f);

            if (feof(f) || ferror(f))
                break;

            fgets(goods[*goods_amount].manufacturer, PRODUCT_MAN_LENGTH, f);

            if (feof(f) || ferror(f))
            {
                exit_code = ERR_INCOMPLETE_STRUCT;
            }

            int result = fscanf(f, "%d", &goods[*goods_amount].price);

            if (result == 1)
                result = fscanf(f, "%d", &goods[*goods_amount].amount);

            if (result == 1)
                (*goods_amount)++;
            else
                exit_code = ERR_INCOMPLETE_STRUCT;
        }
        while (!(feof(f) || ferror(f)));

        if (!feof(f))
            exit_code = ERR_NO_ACCESS;

        fclose(f);
    }
    else
        return ERR_NO_ACCESS;

    return exit_code;
}

int goods_fwrite(char *filename, Product goods[], int goods_amount)
{
    FILE *f = fopen(filename, "w");

    int exit_code = SUCCESS;

    if (f)
    {
        for (int i = 0; i < goods_amount; i++)
        {
            int res = fprintf(f, "%s\n", goods[i].name);

            if (res != 1)
            {
                exit_code = ERR_NO_ACCESS;
                break;
            }

            res = fprintf(f, "%s\n", goods[i].manufacturer);

            if (res != 1)
            {
                exit_code = ERR_NO_ACCESS;
                break;
            }

            res = fprintf(f, "%ud\n", goods[i].price);

            if (res != 1)
            {
                exit_code = ERR_NO_ACCESS;
                break;
            }

            res = fprintf(f, "%ud\n", goods[i].amount);

            if (res != 1)
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
