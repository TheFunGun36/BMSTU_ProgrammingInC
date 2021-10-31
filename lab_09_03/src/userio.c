#include "userio.h"
#include <stdio.h>

static void print_product(product_t prod);

void print_goods(goods_t goods)
{
    for (int i = 0; i < goods.amount; i++)
        print_product(goods.val[i]);
}

static void print_product(product_t prod)
{
    printf("%d\n%s\n", prod.price, prod.name);
}
