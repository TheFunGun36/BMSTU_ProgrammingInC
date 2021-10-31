#include "goods.h"
#include <stdlib.h>
#include <string.h>

exit_t goods_init(goods_t *goods, int amount)
{
    exit_t exit_code = EXIT_SUCCESS;

    if (amount <= 0)
    {
        exit_code = EXIT_INVALID_ARR_SIZE;
    }
    else
    {
        goods->val = (product_t*)calloc(amount, sizeof(product_t));

        if (goods->val)
            goods->amount = amount;
        else
            exit_code = EXIT_NO_MEMORY;
    }

    return exit_code;
}

void goods_free(goods_t *goods)
{
    for (int i = 0; i < goods->amount; i++)
        free(goods->val[i].name);
    free(goods->val);

    memset(goods, 0, sizeof(goods_t));
}

void goods_filter(goods_t *goods, product_t sample, int (*is_ok)(product_t el, product_t sample))
{
    product_t *p_old = goods->val;
    product_t *p_new = goods->val;

    product_t *p_end = goods->val + goods->amount;

    while (p_old < p_end)
    {
        if (is_ok(*p_old, sample))
            *p_new++ = *p_old;
        else
            free(p_old->name);

        p_old++;
    }

    goods->amount = p_new - goods->val;
}
