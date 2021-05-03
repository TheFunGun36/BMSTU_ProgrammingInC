#include <stdio.h>
#include <string.h>

#include "string_work.h"

int main()
{
    char memory[MAX_STRING_LENGTH + 2];

    int exit_code = get_string_from_user(memory, MAX_STRING_LENGTH);

    if (exit_code == OK)
    {
        char *input_str = memory;

        cutoff_spaces(&input_str);

        if (is_phone_number(input_str))
            printf("YES");
        else
            printf("NO");
    }

    return exit_code;
}
