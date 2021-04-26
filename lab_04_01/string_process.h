#ifndef STRING_PROCESS_H
#define STRING_PROCESS_H

const char *my_strpbrk(const char *main_str, const char *small_str);
unsigned int my_strspn(const char *main_str, const char *symbol_set);
unsigned int my_strcspn(const char *main_str, const char *symbol_set);
const char *my_strchr(const char *string, int symbol);
const char *my_strrchr(const char *string, int symbol);

#endif
