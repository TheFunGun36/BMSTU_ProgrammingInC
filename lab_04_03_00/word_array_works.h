#ifndef WORD_ARRAY_WORKS_H
#define WORD_ARRAY_WORKS_H

#define SPLITTERS " ,;:-.!?"

#define MAX_STRING_LENGTH 256
#define MAX_WORD_LENGTH 16
#define OK 0
#define STRING_IS_TOO_LONG -1
#define STRING_IS_TOO_SHORT -2
#define EMPTY_RESULT_ARRAY -3
#define WORD_IS_TOO_LONG -4
#define UNEXPECTED_INPUT_ERROR -5

#define MAX_WORD_AMOUNT MAX_STRING_LENGTH / 2

int split_string(char *string, char *word_to_exclude, char string_array[][MAX_WORD_LENGTH + 1], int *string_array_size);
int pop_last_word(char *string, char **word);
void reverse_word_array(char array[][MAX_WORD_LENGTH + 1], int array_length);
void remove_first_letter_entry(char array[][MAX_WORD_LENGTH + 1], int array_length);
void strarr_to_string(char array[][MAX_WORD_LENGTH + 1], int array_length, char splitter, char *string);

#endif
