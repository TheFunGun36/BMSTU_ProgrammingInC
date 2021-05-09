#include "string_work.h"

#define SPLITTERS " \t\n\r\v\f"

int get_string_from_user(char *string, int max_length)
{
    fgets(string, max_length + 2, stdin);
    string[max_length + 1] = '\0';

    int str_length = strlen(string);

    if (str_length > max_length)
        return STRING_IS_TOO_LONG;

    if (string[str_length - 1] == '\n')
        string[str_length - 1] = '\0';

    return OK;
}

void cutoff_spaces(char **str)
{
    *str += strspn(*str, SPLITTERS);

    *(*str + strcspn(*str, SPLITTERS)) = '\0';
}

int is_phone_number(const char *str)
{
    char *number_set = "0123456789";

    int result = 1;

    if (*str == '+')
    {
        str++;

        int numbers_amount = strspn(str, number_set);
        result = numbers_amount > 0;
        str += numbers_amount;
    }
    else
    {
        int numbers_amount = strspn(str, number_set);
        result = numbers_amount > 0 || *str == '(';
        str += numbers_amount;
    }

    if (strlen(str) != 15)
        return 0;

    result = result && *str == '(' && strspn(str + 1, number_set) == 3 && *(str + 4) == ')';
    str += 5;
    result = result && *str == '-' && strspn(str + 1, number_set) == 3;
    str += 4;
    result = result && *str == '-' && strspn(str + 1, number_set) == 2;
    str += 3;
    result = result && *str == '-' && strspn(str + 1, number_set) == 2;
    str += 3;
    result = result && *str == '\0';

    return result;
}
