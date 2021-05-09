#include "string_process.h"

#define NULL 0x0

char *my_strpbrk(char *main_str, char *symbol_set)
{
    char *result = NULL;

    while (*main_str != '\0')
    {
        for (char *p = symbol_set; *p != '\0'; p++)
        {
            if (*main_str == *p)
                result = main_str;
        }

        if (result)
            break;

        main_str++;
    }

    return result;
}

unsigned int my_strspn(char *main_str, char *symbol_set)
{
    char *mp;

    for (mp = main_str; *mp != '\0'; mp++)
    {
        int is_found = 0;

        for (char *sp = symbol_set; *sp != '\0'; sp++)
        {
            if (*mp == *sp)
            {
                is_found = 1;
                break;
            }
        }

        if (!is_found)
            break;
    }

    return mp - main_str;
}

unsigned int my_strcspn(char *main_str, char *symbol_set)
{
    char *main_str_saved = main_str;
    int is_found = 0;

    while (*main_str != '\0')
    {
        for (char *p = symbol_set; *p != '\0'; p++)
        {
            if (*main_str == *p)
                is_found = 1;
        }

        if (is_found)
            break;

        main_str++;
    }

    return main_str - main_str_saved;
}

char *my_strchr(char *string, int symbol)
{
    char *result = NULL;

    if (*string == symbol)
        result = string;

    if (!result)
    {
        while (*string++ != '\0')
        {
            if (*string == symbol)
            {
                result = string;
                break;
            }
        }
    }

    return result;
}

char *my_strrchr(char *string, int symbol)
{
    char *string_end = string;

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
