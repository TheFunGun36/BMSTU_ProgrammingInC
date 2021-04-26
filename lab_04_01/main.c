#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "string_process.h"

#define OK 0
#define STRING_IS_TOO_LONG -1

#define MAX_STRING_LENGTH 256
#define MAX_WORD_LENGTH 16

int get_string_from_user(char* string, int max_string_length)
{
    int i;
    char chr = getc(stdin);

    for (i = 0; chr != '\n'; i++)
    {
        if (i >= max_string_length)
        {
            string[max_string_length] = '\0';
            return STRING_IS_TOO_LONG;
        }

        string[i] = chr;
        chr = getc(stdin);
    }

    string[i] = '\0';

    return OK;
}

int get_two_strings(char *string1, char *string2)
{
    int result = OK;
    printf("Введите первую строку:\n");
    result = get_string_from_user(string1, MAX_STRING_LENGTH);

    if (result != OK)
        return result;

    printf("Введите вторую строку:\n");
    result = get_string_from_user(string2, MAX_STRING_LENGTH);

    return result;
}

int main()
{
    char string1[MAX_STRING_LENGTH + 1];
    char string2[MAX_STRING_LENGTH + 1];

    setlocale(LC_ALL, "Russian");

    int result = get_two_strings(string1, string2);

    switch (result)
    {
        case OK:
            break;
        case STRING_IS_TOO_LONG:
            printf("Строка слишком длинная\n");
        default:
            printf("Неизвестная ошибка\n");
    }

    if (result != OK)
        return result;

    printf("strpbrk (поиск первого вхождения подстроки в строку):\n");
    printf("\t%s\n", my_strpbrk(string1, string2));

    printf("strspn (длина начального участка str1, сост. из символов str2)\n");
    printf("\t%d\n\n", my_strspn(string1, string2));

    printf("strcspn (первое вхождение любого символа str2 в str1\n");
    printf("\t%d\n\n", my_strcspn(string1, string2));

    printf("\nДалее в качестве символа будет использоваться первый символ второй строки\n");

    printf("strchr (первое вхождение символа в строке)\n");
    printf("\t%s\n\n", my_strchr(string1, *string2));

    printf("strchr (последнее вхождение символа в строке)\n");
    printf("\t%s\n\n", my_strrchr(string1, *string2));

    return OK;
}
