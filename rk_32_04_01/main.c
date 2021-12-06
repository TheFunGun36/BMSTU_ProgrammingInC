#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "student.h"

#define EXIT_OK 0
#define EXIT_NOK 1

int main(int argc, char *argv[])
{
	int exit_code = EXIT_OK;
	
	if (argc == 3 && !strcmp(argv[1], "-f"))
	{
		list_t list;
		list_initialize(&list);
		
		exit_code = file_read_student_list(&list, argv[2]);
		
		while (list.length > 0)
		{
			student_t *student = list_pop_front(&list);
			
			printf("%s %d", student->surname, student->age);
			
			while (student->marks.length > 0)
			{
				int *mark = list_pop_front(&student->marks);
				
				printf(" %d", *mark);
				
				free(mark);
			}
			
			printf("\n");
			
			free(student);
		}
	}
	else
	{
		printf("Key not valid");
	}
	
	return exit_code;
}
