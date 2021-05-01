#ifndef MY_STRING_H
#define MY_STRING_H

typedef struct string
{
    char *begin;
    char *end;
} string;

string get_word(string source_str, int word_count);
int count_word(string source_str, string word);
void print_string(string str);
int is_string_empty(string str);
int is_strings_equal(string str1, string str2);
string str_to_mystr(char* str);
void move_beg_one_word_forward(string *str);
int get_str_size(string str);
int get_max_word_size(string str);

#endif
