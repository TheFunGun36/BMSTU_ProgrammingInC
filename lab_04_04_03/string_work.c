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

    if (strspn(str, "+-") == 1)
        str++;

    int number_length = strspn(str, number_set);

    if (number_length == 0)
        return 0;

    str += number_length;

    if (*str == ' ')
        str++;
    else
        return 0;

    number_length = strspn(str, number_set);

    if (number_length != 3)
        return 0;

    str += number_length;

    if (*str == ' ')
        str++;
    else
        return 0;

    number_length = strspn(str, number_set);

    if (number_length != 3)
        return 0;

    str += number_length;

    if (*str == '-')
        str++;
    else
        return 0;

    number_length = strspn(str, number_set);

    if (number_length != 2)
        return 0;

    str += number_length;

    if (*str == '-')
        str++;
    else
        return 0;

    number_length = strspn(str, number_set);

    if (number_length != 2)
        return 0;

    return *(str + number_length) == '\0';
}
