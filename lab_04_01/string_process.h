#ifndef STRING_PROCESS_H
#define STRING_PROCESS_H

char *my_strpbrk(char *main_str, char *small_str);
unsigned int my_strspn(char *main_str, char *symbol_set);
unsigned int my_strcspn(char *main_str, char *symbol_set);
char *my_strchr(char *string, int symbol);
char *my_strrchr(char *string, int symbol);

#endif
