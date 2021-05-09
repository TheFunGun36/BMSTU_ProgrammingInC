#include "word_array.h"

void strarr_form(string_part str, int arr_len_max, string_part array[], int *array_len)
{
    *array_len = 0;
    string_part word = get_word(str, 0);

    while (!is_string_empty(word) && *array_len < arr_len_max)
    {
        *array++ = word;
        str.begin = word.end;
        (*array_len)++;
        word = get_word(str, 0);
    }
}

void strarr_remove_element_all(string_part *strarr, int *strarr_len, string_part element)
{
    string_part *array_end = strarr + *strarr_len;
    string_part *ptr_new = strarr;

    for (string_part *ptr_old = strarr; ptr_old < array_end; ptr_old++)
    {
        if (!is_strings_equal(*ptr_old, element))
        {
            *ptr_new++ = *ptr_old;
        }
    }

    *strarr_len = ptr_new - strarr;
}

void strarr_form_string(string_part *str, string_part strarr[], int strarr_size, char splitter, int is_reverse)
{
    char *input_str_ptr = str->begin;

    if (is_reverse)
        is_reverse = 1;

    int i_to = (!is_reverse) * strarr_size - is_reverse;
    int incr = 1 - 2 * is_reverse;

    for (int i = is_reverse * (strarr_size - 1); i != i_to; i += incr)
    {
        for (char *p = strarr[i].begin; p < strarr[i].end; p++)
            *input_str_ptr++ = *p;

        *input_str_ptr++ = splitter;
    }

    *(--input_str_ptr) = '\0';
    str->end = input_str_ptr;
}

#ifdef DEBUG

#include <stdio.h>

void strarr_print(string_part strarr[], int strarr_size, char splitter)
{
    for (int i = 0; i < strarr_size; i++)
    {
        print_string(strarr[i]);
        printf("%c", splitter);
    }
}

#endif
