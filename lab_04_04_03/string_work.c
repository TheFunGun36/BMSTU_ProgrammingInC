#include "string_work.h"

#define SPLITTERS " \t\n\r\v\f"
#define PHONE_NUMBER_NO_REGION 15

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
    const char *number_set = "0123456789";

    int result = 1;

    if (*str == '+')
    {
        str++;

        result = *str >= '0' && *str <= '9';
    }

    if (result)
    {
        int numbers_amount = strspn(str, number_set);
        str += numbers_amount;

        result = strlen(str) == PHONE_NUMBER_NO_REGION;
    }

    if (result)
    {
        result = result && *str == '(' && strspn(str + 1, number_set) == 3 && *(str + 4) == ')';
        str += 5; // Код оператора и две скобки
        result = result && *str == '-' && strspn(str + 1, number_set) == 3;
        str += 4; // Дефис и 3 цифры после него
        result = result && *str == '-' && strspn(str + 1, number_set) == 2;
        str += 3; // Дефис и ещё две цифры
        result = result && *str == '-' && strspn(str + 1, number_set) == 2;
        str += 3; // Дефис и последние две цифры
        result = result && *str == '\0';
    }

    return result;
}
