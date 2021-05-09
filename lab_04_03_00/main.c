#include <stdio.h>
#include <string.h>
#include "word_array_works.h"

#define DEBUG

int get_string_from_user(char *string, int max_length)
{
    fgets(string, max_length + 2, stdin);
    //string[max_length + 1] = '\0';

    int str_length = strlen(string);

    if (str_length > max_length)
        return STRING_IS_TOO_LONG;
    if (str_length <= 1)
        return STRING_IS_TOO_SHORT;

    if (string[str_length - 1] == '\n')
        string[str_length - 1] = '\0';

    return OK;
}

int main()
{
    char input_str[MAX_STRING_LENGTH + 2];
    char str_arr[MAX_WORD_AMOUNT][MAX_WORD_LENGTH + 1];

    int exit_code = get_string_from_user(input_str, MAX_STRING_LENGTH);

    if (exit_code == OK)
    {
        int arr_size;

        char *word_to_exclude;

        exit_code = pop_last_word(input_str, &word_to_exclude);

        if (exit_code == OK)
        {
            exit_code = split_string(input_str, word_to_exclude, str_arr, &arr_size);

            if (arr_size <= 0)
                exit_code = EMPTY_RESULT_ARRAY;

            if (exit_code == OK)
            {
                remove_first_letter_entry(str_arr, arr_size);
                reverse_word_array(str_arr, arr_size);
                strarr_to_string(str_arr, arr_size, ' ', input_str);

                if (strlen(input_str) > 0)
                    printf("Result: %s\n", input_str);
                else
                    exit_code = EMPTY_RESULT_ARRAY;
            }
        }
    }

    return exit_code;
}
