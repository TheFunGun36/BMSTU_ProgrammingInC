#ifndef FILE_WORKS_H
#define FILE_WORKS_H

#include <stdio.h>

#define EXIT_SUCCESS 0
#define EXIT_NO_FILE -1
#define EXIT_NO_ACCESS -2

int get_number_by_pos(FILE *f, int position, int *value);
int put_number_by_pos(FILE *f, int position, int value);
int create_file(char *filename, int n);
int print_file_content(char *filename);
int sort_file_content(char *filename);

#endif
