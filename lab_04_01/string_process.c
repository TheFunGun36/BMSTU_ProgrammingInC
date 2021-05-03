#include "string_process.h"

#define NULL 0x0

const char *my_strpbrk(const char *main_str, const char *symbol_set)
{
    const char *result = NULL;

    while (*main_str != '\0')
    {
        if (my_strchr(symbol_set, *main_str) != NULL)
        {
            result = main_str;
            break;
        }

        main_str++;
    }

    return result;
}

unsigned int my_strspn(const char *main_str, const char *symbol_set)
{
    const char *string_begin = main_str;

    while (*main_str != '\0')
    {
        if (my_strchr(symbol_set, *main_str) == NULL)
            break;

        main_str++;
    }

    return main_str - string_begin;
}

unsigned int my_strcspn(const char *main_str, const char *symbol_set)
{
    const char *string_begin = main_str;
    while (*main_str != '\0')
    {
        if (my_strchr(symbol_set, *main_str) != NULL)
            break;

        main_str++;
    }

    return main_str - string_begin;
}

const char *my_strchr(const char *string, int symbol)
{
    if (*string == symbol)
        return string;

    while (*string++ != '\0')
    {
        if (*string == symbol)
            return string;

        string++;
    }

    return NULL;
}

const char *my_strrchr(const char *string, int symbol)
{
    const char *string_end = string;

    while (*string_end != '\0')
        string_end++;

    while (string_end >= string)
    {
        if (*string_end == symbol)
            return string_end;

        string_end--;
    }

    return NULL;
}
