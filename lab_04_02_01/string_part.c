#include <stdio.h>
#include "string_part.h"

char *get_str_end(char *str)
{
    while (*str != '\0')
        str++;

    return str;
}

string_part_t get_empty_string()
{
    string_part_t str;

    str.begin = (char*)0x0;
    str.end = str.begin;

    return str;
}

int is_char_in_string(string_part_t string, char chr)
{
    while (string.begin < string.end)
    {
        if (*string.begin == chr)
            return 1;

        string.begin++;
    }

    return 0;
}

string_part_t get_word(string_part_t source_str, int word_count, string_part_t splitter_set)
{
    string_part_t word;
    word.begin = source_str.begin;
    word.end = word.begin;

    int counter = 0;

    while (word.end < source_str.end)
    {
        while (is_char_in_string(splitter_set, *word.begin) && word.begin < source_str.end)
            word.begin++;

        word.end = word.begin;

        while (!is_char_in_string(splitter_set, *word.end) && *(word.end) != '\0' && word.end < source_str.end)
            word.end++;

        if (word_count == counter++)
            return word;

        word.begin = word.end;
    }

    return get_empty_string();
}

string_part_t find_word(string_part_t source_str, string_part_t word, string_part_t splitter_set)
{
    string_part_t current_word;

    for (int i = 1; source_str.begin < source_str.end; i++)
    {
        current_word = get_word(source_str, 0, splitter_set);

        if (is_strings_equal(current_word, word))
            return current_word;

        move_beg_one_word_forward(&source_str, splitter_set);
    }

    return get_empty_string();
}

int count_word(string_part_t source_str, string_part_t word, string_part_t splitter_set)
{
    int words_found = 0;

    for (int i = 1; source_str.begin < source_str.end; i++)
    {
        string_part_t current_word = get_word(source_str, 0, splitter_set);
        words_found += is_strings_equal(current_word, word);
        move_beg_one_word_forward(&source_str, splitter_set);
    }

    return words_found;
}

void print_string(string_part_t str)
{
    while (str.begin < str.end)
        printf("%c", *(str.begin)++);
}

int is_string_empty(string_part_t str)
{
    return str.begin == str.end;
}

int is_strings_equal(string_part_t str1, string_part_t str2)
{
    if (str1.end - str1.begin == str2.end - str2.begin)
    {
        while (str1.begin < str1.end)
            if (*(str1.begin)++ != *(str2.begin)++)
                return 0;
        return 1;
    }
    return 0;
}

string_part_t get_full_str_part(char *str)
{
    string_part_t my_str;
    my_str.begin = str;
    my_str.end = get_str_end(str);

    return my_str;
}

void move_beg_one_word_forward(string_part_t *str, string_part_t splitter_set)
{
    str->begin = get_word(*str, 1, splitter_set).begin;

    if (str->begin == (char*)0x0)
        str->begin = str->end;
}

int get_str_size(string_part_t str)
{
    return str.end - str.begin;
}

int get_word_max_len(string_part_t str, string_part_t splitter_set)
{
    int word_size_max = 0;
    while (str.begin < str.end)
    {
        int word_size = get_str_size(get_word(str, 0, splitter_set));

        if (word_size > word_size_max)
            word_size_max = word_size;

        move_beg_one_word_forward(&str, splitter_set);
    }

    return word_size_max;
}

void split_into_word_array(string_part_t str, string_part_t splitter_set, int arr_len_max, string_part_t array[], int *array_len)
{
    *array_len = 0;
    string_part_t word = get_word(str, 0, splitter_set);

    while (!is_string_empty(word) && *array_len < arr_len_max)
    {
        *array++ = word;
        str.begin = word.end;
        (*array_len)++;
        word = get_word(str, 0, splitter_set);
    }
}

void split_into_word_set(string_part_t str, string_part_t splitter_set, int arr_len_max, string_part_t array[], int *array_len)
{
    *array_len = 0;
    string_part_t word = get_word(str, 0, splitter_set);
    string_part_t left_part = str;
    left_part.end = str.begin;

    while (!is_string_empty(word) && *array_len < arr_len_max)
    {
        if (is_string_empty(find_word(left_part, word, splitter_set)))
        {
            *array++ = word;
            str.begin = word.end;
            (*array_len)++;
        }

        left_part.end = word.end;
        str.begin = word.end;
        word = get_word(str, 0, splitter_set);
    }
}

string_part_t get_larger_string(string_part_t str1, string_part_t str2)
{
    string_part_t str1_saved = str1;
    string_part_t str2_saved = str2;

    while (str1.begin < str1.end && str2.begin < str2.end)
    {
        if (*str1.begin != *str2.begin)
        {
            if (*str1.begin > *str2.begin)
                return str1_saved;
            else
                return str2_saved;
        }

        str1.begin++;
        str2.begin++;
    }

    if (!is_string_empty(str1))
        return str1_saved;
    else if (!is_string_empty(str2))
        return str2_saved;

    return get_empty_string();
}

int string_compare(string_part_t str1, string_part_t str2)
{
    while (str1.begin < str1.end && str2.begin < str2.end)
    {
        if (*str1.begin != *str2.begin)
        {
            if (*str1.begin > *str2.begin)
                return 1;
            else
                return -1;
        }

        str1.begin++;
        str2.begin++;
    }

    if (is_string_empty(str1))
        return -1;
    else if (is_string_empty(str2))
        return 1;

    return 0;
}
