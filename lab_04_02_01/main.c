#include <stdio.h>
#include "string_part.h"

#define OK 0
#define STRING_IS_TOO_LONG -1
#define WORD_IS_TOO_LONG -2

#define MAX_STRING_LENGTH 256
#define MAX_WORD_LENGTH 16
#define MAX_WORD_AMOUNT MAX_STRING_LENGTH / 2

#define WORD_SPLITTER ' '

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

void sort_string_array(string_part array[], int array_len)
{
    string_part *array_end = array + array_len;

    for (string_part *current_element = array; current_element < array_end; current_element++)
    {
        for (string_part *new_place = array; new_place < current_element; new_place++)
        {
            if (is_strings_equal(*new_place, get_larger_string(*new_place, *current_element)))
            {
                string_part saved_element = *current_element;

                for (string_part *p = current_element; p > new_place; p--)
                    *p = *(p - 1);

                *new_place = saved_element;
            }
        }
    }
}

int main()
{
    char str_beg[MAX_STRING_LENGTH + 1];

    int exit_code = get_string_from_user(str_beg, MAX_STRING_LENGTH);

    if (exit_code == OK)
    {
        string_part str = get_full_str_part(str_beg);

        exit_code += (get_word_max_len(str, WORD_SPLITTER) > MAX_WORD_LENGTH) * WORD_IS_TOO_LONG;

        if (exit_code == OK)
        {
            string_part str_array[MAX_WORD_AMOUNT];
            int str_array_size;
            split_into_word_set(str, WORD_SPLITTER, MAX_WORD_AMOUNT, str_array, &str_array_size);
            sort_string_array(str_array, str_array_size);

            printf("Result: ");

            for (int i = 0; i < str_array_size; i++)
            {
                print_string(str_array[i]);
                printf(" ");
            }
        }
    }

    return exit_code;
}
