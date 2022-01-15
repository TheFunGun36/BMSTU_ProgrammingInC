#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>

#define FILE_OK 0
#define FILE_FAIL 1
#define FILE_ENDL 2
#define FILE_SPACE 3
#define FILE_MEMORY 4
#define FILE_NOT_FOUND 5
#define FILE_EOF -1

int file_read_word(FILE *f, char *str, int max_sz);
int file_read_number(FILE *f, int *val);
int file_read_endl(FILE *f);

#endif
