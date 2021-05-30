#ifndef FILEIO_H
#define FILEIO_H
#include <stdio.h>
#include "goods.h"

int product_fread(FILE *f, product_t *product);

int goods_fread(char *filename, product_t goods[], int *goods_amount);
int goods_fwrite(char *filename, product_t goods[], int goods_amount);

int goods_print(product_t goods[], int goods_amount, char *name_endl_mask);

#endif
