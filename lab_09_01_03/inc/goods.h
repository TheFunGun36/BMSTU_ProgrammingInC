#ifndef GOODS_H
#define GOODS_H

#include "exit_code.h"

typedef struct
{
    int price;
    char *name;
} product_t;

typedef struct
{
    int amount;
    product_t *val;
} goods_t;

exit_t goods_init(goods_t *goods, int amount);
void goods_free(goods_t *goods);

void goods_filter(goods_t *goods, product_t sample, int (*is_ok)(product_t el, product_t sample));

#endif
