#include "fileio.h"

int file_read_word(FILE *f, char *str, int max_sz)
{
	if (!f)
		return FILE_FAIL;
	
	int res;
	char *ptr = str;
	do
	{
		res = fscanf(f, "%c", ptr);
	} while (*ptr++ != ' ' && res == 1);
	
	*(--ptr) = '\0';
	
	return (res == 1) ? FILE_OK : FILE_FAIL;
}

int file_read_number(FILE *f, int *val)
{
	if (!f)
		return FILE_FAIL;
	
	int res = FILE_OK;
	
	if (fscanf(f, "%d", val) != 1)
		res = FILE_FAIL;
		
	return res;
}

int file_read_endl(FILE *f)
{
	if (!f)
		return FILE_FAIL;
	
	char tmp;
	int res = fscanf(f, "%c", &tmp);
	
	if (res == 1)
	{
		switch (tmp)
		{
			case '\n': res = FILE_ENDL; break;
			case ' ': res = FILE_SPACE; break;
			default: res = FILE_FAIL; break;
		}
	}
	else if (res == 0)
	{
		res = FILE_FAIL;
	}
	else
	{
		res = FILE_EOF;
	}
	
	return res;
}
