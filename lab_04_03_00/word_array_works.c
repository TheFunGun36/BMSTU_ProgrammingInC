#include <string.h>
#include "word_array_works.h"

int split_string(char *string, char *word_to_exclude, char string_array[][MAX_WORD_LENGTH + 1], int *string_array_size)
{
    char *word = strtok(string, SPLITTERS);
    *string_array_size = 0;

    while (word != NULL)
    {
        int i;

        for (i = 0; i <= MAX_WORD_LENGTH; i++)
        {
            if (word[i] == '\0')
                break;
        }

        if (i > MAX_WORD_LENGTH)
            return WORD_IS_TOO_LONG;

        strncpy(string_array[*string_array_size], word, MAX_WORD_LENGTH + 1);

        if (strncmp(string_array[*string_array_size], word_to_exclude, MAX_WORD_LENGTH))
            (*string_array_size)++;

        word = strtok(NULL, SPLITTERS);
    }

    return OK;
}

int pop_last_word(char *string, char **word)
{
    char *p = string + strlen(string) - 1;

    while (p > string && strchr(SPLITTERS, *p))
        p--;

    *(p + 1) = '\0';

    while (p > string && !strchr(SPLITTERS, *p))
        p--;

    *word = p + 1;

    if (strlen(*word) > MAX_WORD_LENGTH)
        return WORD_IS_TOO_LONG;

    *p = '\0';

    return OK;
}

void swap_strings(char *str1, char *str2)
{
    char *tmp[MAX_WORD_LENGTH + 1];
    strcpy(tmp, str1);
    strcpy(str1, str2);
    strcpy(str2, tmp);
}

void reverse_word_array(char array[][MAX_WORD_LENGTH + 1], int array_length)
{
    int j = array_length - 1;

    for (int i = 0; i < j; i++)
    {
        swap_strings(array[i], array[j]);

        j--;
    }
}

void wrd_rm_first_letter_entry(char *word)
{
    char letter = *word;
    char *p_new = word + 1;

    for (char *p_old = word + 1; *p_old != '\0'; p_old++)
    {
        *p_new = *p_old;

        if (*p_old != letter)
            p_new++;
    }

    *p_new = '\0';
}


void remove_first_letter_entry(char array[][MAX_WORD_LENGTH + 1], int array_length)
{
    for (int i = 0; i < array_length; i++)
        wrd_rm_first_letter_entry(array[i]);
}

void strarr_to_string(char array[][MAX_WORD_LENGTH + 1], int array_length, char splitter, char *string)
{
    for (int i = 0; i < array_length; i++)
    {
        int word_len = strlen(array[i]);
        strcpy(string, array[i]);
        string += word_len;

        *string = splitter;
        string++;
    }

    string--;
    *string = '\0';
}
