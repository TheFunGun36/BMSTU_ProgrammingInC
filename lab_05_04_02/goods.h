#ifndef GOODS_H
#define GOODS_H

#define PRODUCT_NAME_LENGTH 32
#define PRODUCT_MAN_LENGTH 17
#define GOODS_MAX_AMOUNT 101

#define EXIT_SUCCESS 0
#define ERR_NO_ACCESS -1
#define ERR_INCOMPLETE_STRUCT -2
#define ERR_EMPTY_STRING -3
#define ERR_LONG_STRING -4
#define ERR_FILE_IS_TOO_LONG -5
#define ERR_NOTHING_TO_PRINT -6
#define ERR_NOTHING_TO_SORT -7

typedef struct
{
    char name[PRODUCT_NAME_LENGTH];
    char manufacturer[PRODUCT_MAN_LENGTH];
    unsigned int price;
    unsigned int amount;
} product_t;

int is_valid_product(product_t product);

void goods_sort_price_descend(product_t goods[], int goods_amount);
void goods_insert(product_t goods[], int *goods_amount, product_t new_product);

#endif
