#ifndef STRING_WORK_H
#define STRING_WORK_H

#include <stdio.h>
#include <string.h>

#define OK 0
#define STRING_IS_TOO_LONG -1
#define WORD_IS_TOO_LONG -2

#define MAX_STRING_LENGTH 256

int get_string_from_user(char *string, int max_length);
void cutoff_spaces(char **str);
int is_phone_number(const char *str);

#endif
