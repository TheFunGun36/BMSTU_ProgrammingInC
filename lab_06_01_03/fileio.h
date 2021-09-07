#ifndef FILEIO_H
#define FILEIO_H

#include "product.h"

#define EXIT_SUCCESS 0
#define EXIT_FILE_NOT_OPENED -1
#define EXIT_LINE_NOT_READ -2
#define EXIT_EMPTY_INPUT_STRING -3
#define EXIT_LONG_INPUT_STRING -4
#define EXIT_INVALID_NUMBER -5
#define EXIT_INVALID_PRODUCTS_AMOUNT -6
#define EXIT_FILEIO_LAST -7

#define MAX_PRODUCTS_AMOUNT 15

int read_product_arr(product_t *product_arr, unsigned int *product_arr_size, char *filename);

#endif
