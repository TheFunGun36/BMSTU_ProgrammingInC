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
    printf("%s\n%d\n", prod.name, prod.price);
}
