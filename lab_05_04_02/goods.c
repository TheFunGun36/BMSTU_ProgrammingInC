#include <stdio.h>
#include <string.h>
#include "goods.h"

void goods_sort_price_descend(product_t goods[], int goods_amount)
{
    product_t tmp;

    for (int i = 1; i < goods_amount; i++)
    {
        for (int j = i - 1; j >= 0 && (goods[j].price < goods[j + 1].price || (goods[j].price == goods[j + 1].price && goods[j].amount < goods[j + 1].amount)); j--)
        {
            tmp = goods[j];
            goods[j] = goods[j + 1];
            goods[j + 1] = tmp;
        }
    }
}

void goods_insert(product_t goods[], int *goods_amount, product_t new_product)
{
    product_t tmp;
    (*goods_amount)++;
    goods[*goods_amount - 1] = new_product;

    for (int j = *goods_amount - 2; j >= 0 && (goods[j].price < new_product.price || (goods[j].price == new_product.price && goods[j].amount < new_product.amount)); j--)
    {
        tmp = goods[j];
        goods[j] = goods[j + 1];
        goods[j + 1] = tmp;
    }
}
