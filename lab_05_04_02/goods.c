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
        for (int j = i - 1; j >= 0 && (goods[j].price < goods[j + 1].price || (goods[j].price == goods[j + 1].price && goods[j].amount < goods[j + 1].amount)); j--)
        {
            product_t tmp1 = goods[j];
            goods[j] = goods[j + 1];
            goods[j + 1] = tmp1;
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
