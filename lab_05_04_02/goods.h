#ifndef GOODS_H
#define GOODS_H

#define PRODUCT_NAME_LENGTH 31
#define PRODUCT_MAN_LENGTH 16

#define SUCCESS 0
#define ERR_NO_ACCESS -1
#define ERR_INCOMPLETE_STRUCT -2

typedef struct Product
{
    char name[PRODUCT_NAME_LENGTH];
    char manufacturer[PRODUCT_MAN_LENGTH];
    unsigned int price;
    unsigned int amount;
} Product;

int is_valid_product(Product product);

void goods_sort_price_descend(Product goods[], int goods_amount);
void goods_print(Product goods[], int goods_amount, char *name_endl_mask);
void goods_insert(Product goods[], int *goods_amount, Product new_product);

int goods_fread(char *filename, Product goods[], int *goods_amount);
int goods_fwrite(char *filename, Product goods[], int goods_amount);

#endif
