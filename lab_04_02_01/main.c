#include <stdio.h>
#include "my_string.h"

#define OK 0
#define STRING_IS_TOO_LONG -1
#define WORD_IS_TOO_LONG -2

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

void print_words(string main_str)
{
    string left_part = main_str;
    string right_part = main_str;

    string current_word = get_word(right_part, 0);

    while (!is_string_empty(current_word))
    {
        left_part.end = current_word.begin;
        right_part.begin = current_word.begin;

        if (!count_word(left_part, current_word))
        {
            print_string(current_word);

            int words_amount = count_word(right_part, current_word);
            printf(" %d\n", words_amount);
        }

        move_beg_one_word_forward(&right_part);
        left_part.end = right_part.begin;
        current_word = get_word(right_part, 0);
    }
}

int main()
{
    char str_beg[MAX_STRING_LENGTH + 1];

    int exit_code = get_string_from_user(str_beg, MAX_STRING_LENGTH);

    if (exit_code == OK)
    {
        string str = str_to_mystr(str_beg);

        exit_code += (get_max_word_size(str) > MAX_WORD_LENGTH) * WORD_IS_TOO_LONG;

        if (exit_code == OK)
        {
            print_words(str);
        }
    }

    return exit_code;
}
