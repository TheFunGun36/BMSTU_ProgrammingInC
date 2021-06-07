#ifndef STRING_PART_H
#define STRING_PART_H

typedef struct string_part_t
{
    char *begin;
    char *end;
} string_part_t;

string_part_t get_empty_string();
string_part_t get_word(string_part_t source_str, int word_index, string_part_t splitter_set);
string_part_t find_word(string_part_t source_str, string_part_t word, string_part_t splitter_set);
int count_word(string_part_t source_str, string_part_t word, string_part_t splitter_set);
void print_string(string_part_t str);
int is_string_empty(string_part_t str);
int is_strings_equal(string_part_t str1, string_part_t str2);
string_part_t get_full_str_part(char *str);
void move_beg_one_word_forward(string_part_t *str, string_part_t splitter_set);
int get_str_size(string_part_t str);
int get_word_max_len(string_part_t str, string_part_t splitter_set);
void split_into_word_array(string_part_t str, string_part_t splitter_set, int arr_len_max, string_part_t array[], int *array_len);
void split_into_word_set(string_part_t str, string_part_t splitter_set, int arr_len_max, string_part_t array[], int *array_len);
string_part_t get_larger_string(string_part_t str1, string_part_t str2);
int string_compare(string_part_t str1, string_part_t str2);

#endif
