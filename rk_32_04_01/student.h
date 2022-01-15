#ifndef STUDENT_H
#define STUDENT_H

#include "list.h"
#include "fileio.h"

#define SURNAME_MAX_LENGTH 255

typedef struct
{
	char surname[SURNAME_MAX_LENGTH];
	int age;
	list_t marks;
} student_t;

int file_read_student_list(list_t *list, char *filename);

#endif
