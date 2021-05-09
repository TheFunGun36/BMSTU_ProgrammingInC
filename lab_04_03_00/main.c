#include <stdio.h>
#include <string.h>
//#include "word_array.h"
#include "word_array_works.h"

#define DEBUG

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

int main()
{
    char input_str[MAX_STRING_LENGTH + 1];

    int exit_code = get_string_from_user(input_str, MAX_STRING_LENGTH);

    if (exit_code != OK)
    {
        return exit_code;
    }
    else
    {
        char str_arr[MAX_WORD_AMOUNT][MAX_WORD_LENGTH + 1];
        int arr_size;

        char *word_to_exclude;
        char *input_str_ptr = input_str;

        exit_code = pop_last_word(input_str_ptr, &word_to_exclude);

        if (exit_code != OK)
            return exit_code;

        exit_code = split_string(input_str, word_to_exclude, str_arr, &arr_size);

        if (exit_code != OK)
            return exit_code;

        remove_first_letter_entry(str_arr, arr_size);
        reverse_word_array(str_arr, arr_size);

        strarr_to_string(str_arr, arr_size, ' ', input_str);

        printf("Result: %s\n", input_str);
        //aaaaaaaaa abc abc def asldfkj abc def ded def
    }

    return exit_code;
}
