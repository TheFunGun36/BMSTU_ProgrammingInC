#ifndef STRING_PART_H
#define STRING_PART_H

typedef struct string_part
{
    char *begin;
    char *end;
} string_part;

string_part get_empty_string();
string_part get_word(string_part source_str, int word_index, string_part splitter_set);
string_part find_word(string_part source_str, string_part word, string_part splitter_set);
int count_word(string_part source_str, string_part word, string_part splitter_set);
void print_string(string_part str);
int is_string_empty(string_part str);
int is_strings_equal(string_part str1, string_part str2);
string_part get_full_str_part(char *str);
void move_beg_one_word_forward(string_part *str, string_part splitter_set);
int get_str_size(string_part str);
int get_word_max_len(string_part str, string_part splitter_set);
void split_into_word_array(string_part str, string_part splitter_set, int arr_len_max, string_part array[], int *array_len);
void split_into_word_set(string_part str, string_part splitter_set, int arr_len_max, string_part array[], int *array_len);
string_part get_larger_string(string_part str1, string_part str2);

#endif
