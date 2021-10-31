#ifndef FILEIO_H
#define FILEIO_H

#include "exit_code.h"
#include "goods.h"

exit_t file_read_goods(char *filename, goods_t *goods);

#endif
