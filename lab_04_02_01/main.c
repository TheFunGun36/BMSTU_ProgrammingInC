#include <stdio.h>
#include "string_part.h"

#define OK 0
#define EMPTY_STRING -1
#define STRING_IS_TOO_LONG -2
#define WORD_IS_TOO_LONG -3

#define MAX_STRING_LENGTH 256
#define MAX_WORD_LENGTH 16
#define MAX_WORD_AMOUNT MAX_STRING_LENGTH / 2

#define SPLITTERS " ,;:-.!?"

int get_string_from_user(char *string, int max_string_length)
{
    int i;
    char chr = getc(stdin);

    for (i = 0; chr != '\n' && chr != '\0'; i++)
    {
        if (i >= max_string_length)
        {
            string[max_string_length] = '\0';
            return STRING_IS_TOO_LONG;
        }

        string[i] = chr;
        chr = getc(stdin);
    }

    if (i == 0)
        return EMPTY_STRING;

    string[i] = '\0';

    return OK;
}

void sort_word_array(string_part_t array[], int array_len)
{
    for (int i = 1; i < array_len; i++)
    {
        int j;
        for (j = i - 1; string_compare(array[j], array[j + 1]) > 0 && j >= 0; j--)
        {
            string_part_t tmp = array[j];
            array[j] = array[j + 1];
            array[j + 1] = tmp;
        }

        j++;
    }
}

int wrap_str_to_string_part(char *input_string, string_part_t *string_part, string_part_t *splitter_set)
{
    int exit_code = get_string_from_user(input_string, MAX_STRING_LENGTH);

    if (exit_code == OK)
    {
        *string_part = get_full_str_part(input_string);
        *splitter_set = get_full_str_part(SPLITTERS);

        if (get_word_max_len(*string_part, *splitter_set) > MAX_WORD_LENGTH)
            exit_code = WORD_IS_TOO_LONG;
    }

    if (exit_code == OK)
    {
        string_part_t first_word = get_word(*string_part, 0, *splitter_set);

        if (first_word.begin == string_part->end)
            exit_code = EMPTY_STRING;
    }

    return exit_code;
}

void print_word_list(string_part_t word_list[], int words_amount)
{
    printf("Result: ");

    for (int i = 0; i < words_amount; i++)
    {
        print_string(word_list[i]);
        printf(" ");
    }
}

int main()
{
    char input_string[MAX_STRING_LENGTH + 1];
    string_part_t input_string_part;
    string_part_t splitter_set = get_full_str_part(SPLITTERS);

    int exit_code = wrap_str_to_string_part(input_string, &input_string_part, &splitter_set);

    if (exit_code == OK)
    {
        string_part_t word_list[MAX_WORD_AMOUNT];
        int words_amount;

        split_into_word_set(input_string_part, splitter_set, MAX_WORD_AMOUNT, word_list, &words_amount);
        sort_word_array(word_list, words_amount);

        print_word_list(word_list, words_amount);
    }

    return exit_code;
}
