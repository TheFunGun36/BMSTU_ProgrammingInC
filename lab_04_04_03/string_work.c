#include "string_work.h"

int get_string_from_user(char *string, int max_length)
{
    fgets(string, max_length + 2, stdin);
    string[max_length + 1] = '\0';

    int str_length = strlen(string);

    if (str_length > max_length)
        return STRING_IS_TOO_LONG;
    if (str_length <= 0)
        return STRING_IS_TOO_LONG;

    string[str_length - 1] = '\0';
    return OK;
}

void cutoff_spaces(char **str)
{
    char *ptr = *str;

    while (*ptr == ' ')
        ptr++;

    *str = ptr;

    ptr += strlen(ptr) - 1;

    while (*ptr == ' ')
        ptr--;

    *(ptr + 1) = '\0';
}

int is_phone_number(const char *str)
{
    char *number_set = "0123456789";

    int result = strspn(str, number_set) == 3 || (*str == '+' && strspn(++str, number_set) > 3);
    str += strspn(str, number_set);

    result = result && *str == '-' && strspn(str + 1, number_set) == 3;
    str += 4;
    result = result && *str == '-' && strspn(str + 1, number_set) == 2;
    str += 3;
    result = result && *str == '-' && strspn(str + 1, number_set) == 2;
    str += 3;
    result = result && *str == '\0';

    return result;
}
