#include <string.h>
#include "word_array_works.h"

int split_string(char *string, char *word_to_exclude, char string_array[][MAX_WORD_LENGTH + 1], int *string_array_size)
{
    char *word = strtok(string, SPLITTERS);
    *string_array_size = 0;

    while (word != NULL)
    {
        int result = -1;

        for (int i = MAX_WORD_LENGTH; i >= 0; i--)
        {
            if (word[i] == '\0')
            {
                result = i;
                break;
            }
        }

        if (result < 0)
            return WORD_IS_TOO_LONG;

        strncpy(string_array[*string_array_size], word, MAX_WORD_LENGTH + 1);

        if (strcmp(string_array[*string_array_size], word_to_exclude))
            (*string_array_size)++;

        word = strtok(NULL, SPLITTERS);
    }

    return OK;
}

int pop_last_word(char *string, char **word)
{
    char *p = string + strlen(string) - 1;

    while (p > string && !strchr(SPLITTERS, *p))
        p--;

    *word = p + 1;

    if (strlen(*word) > MAX_WORD_LENGTH)
        return WORD_IS_TOO_LONG;

    *p = '\0';

    return OK;
}

void reverse_word_array(char array[][MAX_WORD_LENGTH + 1], int array_length)
{
    for (int i = 0; i < array_length / 2; i++)
    {
        int j = 0;
        char tmp;

        while (array[i][j] != '\0' && array[array_length - i - 1][j] != '\0')
        {
            tmp = array[i][j];
            array[i][j] = array[array_length - i - 1][j];
            array[array_length - i - 1][j] = tmp;

            j++;
        }

        tmp = array[i][j];
        array[i][j] = array[array_length - i - 1][j];
        array[array_length - i - 1][j] = tmp;

        if (array[i][j] == '\0')
        {
            j++;

            while (array[i][j] != '\0')
            {
                array[array_length - i - 1][j] = array[i][j];
                j++;
            }

            array[array_length - i - 1][j] = '\0';
        }
        else if (array[array_length - i - 1][j] == '\0')
        {
            j++;

            while (array[array_length - i - 1][j] != '\0')
            {
                array[i][j] = array[array_length - i - 1][j];
                j++;
            }

            array[i][j] = '\0';
        }
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
        for (int j = 0; array[i][j] != '\0'; j++)
        {
            *string++ = array[i][j];
        }

        *string++ = splitter;
    }

    *(--string) = '\0';
}
