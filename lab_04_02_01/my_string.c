#include <stdio.h>
#include "my_string.h"

char* get_str_end(char* str)
{
    while (*str != '\0')
        str++;

    return str;
}

string get_word(string source_str, int word_count)
{
    string word;
    word.begin = source_str.begin;
    word.end = word.begin;

    int counter = 0;

    while (word.end < source_str.end)
    {
        while (*(word.begin) == ' ' && word.begin < source_str.end)
            word.begin++;

        word.end = word.begin;

        while (*(word.end) != ' ' && *(word.end) != '\0' && word.end < source_str.end)
            word.end++;

        if (word_count == counter++)
            return word;

        word.begin = word.end;
    }

    word.begin = (char*)0x0;
    word.end = word.begin;

    return word;
}

int count_word(string source_str, string word)
{
    int words_found = 0;

    for (int i = 1; source_str.begin < source_str.end; i++)
    {
        string current_word = get_word(source_str, 0);
        words_found += is_strings_equal(current_word, word);
        move_beg_one_word_forward(&source_str);
    }

    return words_found;
}

void print_string(string str)
{
    while (str.begin < str.end)
        printf("%c", *(str.begin)++);
}

int is_string_empty(string str)
{
    return str.begin == str.end;
}

int is_strings_equal(string str1, string str2)
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

string str_to_mystr(char* str)
{
    string my_str;
    my_str.begin = str;
    my_str.end = get_str_end(str);

    return my_str;
}

void move_beg_one_word_forward(string *str)
{
    str->begin = get_word(*str, 1).begin;

    if (str->begin == (char*)0x0)
        str->begin = str->end;
}

int get_str_size(string str)
{
    return str.end - str.begin;
}

int get_max_word_size(string str)
{
    int word_size_max = 0;
    while (str.begin < str.end)
    {
        int word_size = get_str_size(get_word(str, 0));

        if (word_size > word_size_max)
            word_size_max = word_size;

        move_beg_one_word_forward(&str);
    }

    return word_size_max;
}
