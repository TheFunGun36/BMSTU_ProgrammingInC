#ifndef WORD_ARRAY_H
#define WORD_ARRAY_H

#include "string_part.h"

void strarr_form(string_part str, char splitter, int arr_len_max, string_part array[], int *array_len);
void strarr_form_set(string_part str, char splitter, int arr_len_max, string_part array[], int *array_len);
void strarr_remove_element_all(string_part *strarr, int *strarr_len, string_part element);
void strarr_form_string(string_part *str, string_part strarr[], int strarr_size, char splitter, int is_reverse);

#ifdef DEBUG
void strarr_print(string_part strarr[], int strarr_size, char splitter);
#endif

#endif
