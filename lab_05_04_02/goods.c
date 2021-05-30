#include <stdio.h>
#include <string.h>
#include "goods.h"

int is_valid_product(product_t product)
{
    int result = strlen(product.name) >= PRODUCT_NAME_LENGTH;
    result |= strlen(product.manufacturer) >= PRODUCT_MAN_LENGTH;
    return result;
}

void goods_sort_price_descend(product_t goods[], int goods_amount)
{
    for (int i = 1; i < goods_amount; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (goods[j].price < goods[i].price || (goods[j].price == goods[i].price && goods[j].amount < goods[i].amount))
            {
                product_t tmp = goods[j];

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

void goods_insert(product_t goods[], int *goods_amount, product_t new_product)
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
