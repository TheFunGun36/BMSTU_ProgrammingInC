#include <stdio.h>
#include <string.h>

#include "string_work.h"

#define STR_LEN 5
#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1

int main()
{
    char memory[MAX_STRING_LENGTH + 2];

    int exit_code = get_string_from_user(memory, MAX_STRING_LENGTH);

    if (exit_code == OK)
    {
        char *input_str = memory;

        cutoff_spaces(&input_str);

        if (is_phone_number(input_str))
            printf("YES\n");
        else
            printf("NO\n");
    }

    return exit_code;
}
