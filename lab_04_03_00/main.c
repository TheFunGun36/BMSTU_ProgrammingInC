#include <stdio.h>
#include <string.h>
#include "string_part.h"
#include "word_array.h"

#undef DEBUG

#define OK 0
#define STRING_IS_TOO_LONG -1
#define STRING_IS_TOO_SHORT -2
#define WORD_IS_TOO_LONG -3
#define EMPTY_RESULT_ARRAY -4

#define MAX_STRING_LENGTH 256
#define MAX_WORD_LENGTH 16
#define MAX_WORD_AMOUNT MAX_STRING_LENGTH / 2

int get_string_from_user(char *string, int max_length)
{
    fgets(string, max_length + 2, stdin);
    string[max_length + 1] = '\0';

    int str_length = strlen(string);

    if (str_length > max_length)
        return STRING_IS_TOO_LONG;
    if (str_length <= 0)
        return STRING_IS_TOO_SHORT;

    if (string[str_length - 1] == '\n')
        string[str_length - 1] = '\0';

    return OK;
}

void foreach_strarr_element(string_part strarr[], int *strarr_len)
{
    int i_new = 0;

    for (int i_old = 0; i_old < *strarr_len; i_old++)
    {
        char symbol = *strarr[i_old].begin;
        remove_symbol(&strarr[i_old], symbol);
        strarr[i_new] = strarr[i_old];

        i_new += !is_string_empty(strarr[i_old]);
    }

    *strarr_len = i_new;
}

int main()
{
    char input_str[MAX_STRING_LENGTH + 2];

    int exit_code = get_string_from_user(input_str, MAX_STRING_LENGTH);

    if (exit_code != OK)
    {
        return exit_code;
    }
    else
    {
        string_part input_str_part = get_full_str_part(input_str);

        char splitter_set_mem[] = " ,;:-.!?";
        string_part splitter_set = get_full_str_part(splitter_set_mem);

        if (get_word(input_str_part, 0, splitter_set).begin == input_str_part.end)
            return EMPTY_RESULT_ARRAY;

        if (get_word_max_len(input_str_part, splitter_set) >= MAX_WORD_LENGTH)
            return WORD_IS_TOO_LONG;

        string_part word_list[MAX_WORD_AMOUNT];
        int word_list_size;

        char output_str[MAX_STRING_LENGTH + 2];
        string_part output_str_part = get_full_str_part(output_str);

        strarr_form(input_str_part, splitter_set, MAX_WORD_AMOUNT, word_list, &word_list_size);

        if (word_list_size <= 0)
            return EMPTY_RESULT_ARRAY;

        strarr_remove_element_all(word_list, &word_list_size, word_list[word_list_size - 1]);

        if (word_list_size <= 0)
            return EMPTY_RESULT_ARRAY;

        foreach_strarr_element(word_list, &word_list_size);

        if (word_list_size <= 0)
            return EMPTY_RESULT_ARRAY;

        strarr_form_string(&output_str_part, word_list, word_list_size, ' ', 1);
        printf("Result: ");
        print_string(output_str_part);
        printf("\n");
    }

    return exit_code;
}
