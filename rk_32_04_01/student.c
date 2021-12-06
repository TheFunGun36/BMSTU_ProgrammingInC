#include "student.h"
#include <stdlib.h>

static int file_read_student(student_t *student, FILE *f);

int file_read_student_list(list_t *list, char *filename)
{
	int exit_code = FILE_OK;
	
	FILE *f = fopen(filename, "rt");
	
	if (!f)
		exit_code = FILE_NOT_FOUND;
		
	while (exit_code == FILE_OK)
	{
		student_t *student = calloc(1, sizeof(student_t));
		
		if (student)
		{
			exit_code = file_read_student(student, f);
			
			if (exit_code == FILE_OK)
				list_push_back(list, student);
		}
		else
		{
			exit_code = FILE_MEMORY;
		}
	}
	
	if (f)
		fclose(f);
	
	return exit_code;
}

int file_read_student(student_t *student, FILE *f)
{
	int exit_code = file_read_word(f, student->surname, SURNAME_MAX_LENGTH);
	
	if (exit_code == FILE_OK)
		exit_code = file_read_number(f, &student->age);
	
	int *mark;
	
	do
	{
		mark = malloc(sizeof(int));
		
		if (mark)
		{
			exit_code = file_read_number(f, mark);
		
			if (exit_code == FILE_OK)
				exit_code = list_push_back(&student->marks, mark);
			else if (exit_code == FILE_EOF)
				exit_code = FILE_FAIL;
			
			if (exit_code == LIST_OK)
				exit_code = file_read_endl(f);
		}
		else
		{
			exit_code = FILE_MEMORY;
		}
	}
	while (exit_code == FILE_SPACE);
	
	if (exit_code == FILE_ENDL)
		exit_code = FILE_OK;
	
	return exit_code;
}