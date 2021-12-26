#ifndef FILEIO_H
#define FILEIO_H

#include "field.h"

#define EXIT_SUCCESS 0
#define EXIT_NO_MEMORY 1
#define EXIT_FILE_OPEN 2
#define EXIT_FILE_INV_CONTENT 3

int fload_field(field_t *state, char *filename);

#endif
