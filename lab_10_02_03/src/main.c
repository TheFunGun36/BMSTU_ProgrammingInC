#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exit_code.h"
#include "list.h"
#include "dynamic_array.h"
#include "big_number.h"

#define MAX_CMD_SZ 3

#define CMD_UNKNOWN 0
#define CMD_OUT 1
#define CMD_MUL 2
#define CMD_SQR 3
#define CMD_DIV 4

int input_cmd();
exit_t input_numbers(node_t **bn1, node_t **bn2);

int main()
{
    int cmd = input_cmd();
    exit_t exit_code = cmd == CMD_UNKNOWN ? exit_invalid_cmd : exit_success;

    if (exit_code == exit_success)
    {
        node_t *bn1 = NULL;
        node_t *bn2 = NULL;
        switch (cmd)
        {
            case CMD_OUT:
                exit_code = input_numbers(&bn1, NULL);

                if (exit_code == exit_success)
                {
                    if (bn1)
                        bign_print(bn1);
                    else
                        exit_code = exit_empty_output;
                }
                break;
            case CMD_MUL:
                exit_code = input_numbers(&bn1, &bn2);

                if (exit_code == exit_success)
                {
                    bn1 = bign_multiply(&bn1, &bn2);
                    
                    if (bn1)
                        bign_print(bn1);
                    else
                        exit_code = exit_empty_output;
                }
                break;
            case CMD_SQR:
                exit_code = input_numbers(&bn1, NULL);
                
                if (exit_code == exit_success)
                {
                    if (bn1)
                    {
                        bign_square(bn1);
                        bign_print(bn1);
                    }
                    else
                    {
                        exit_code = exit_empty_output;
                    }
                }
                break;
            case CMD_DIV:
                exit_code = input_numbers(&bn1, &bn2);

                if (exit_code == exit_success)
                {
                    int found_negatives;
                    bn1 = bign_divide(&bn1, &bn2, &found_negatives);

                    if (found_negatives)
                        clear(&bn1, 1);

                    if (bn1)
                        bign_print(bn1);
                    else
                        exit_code = exit_empty_output;
                }
                break;
        }

        clear(&bn1, 1);
        clear(&bn2, 1);
    }

    return exit_code;
}

int input_cmd()
{
    int result = CMD_UNKNOWN;

    char input[MAX_CMD_SZ + 3];
    if (fgets(input, MAX_CMD_SZ + 3, stdin))
    {
        if (!strcmp(input, "out\n"))
            result = CMD_OUT;
        else if (!strcmp(input, "mul\n"))
            result = CMD_MUL;
        else if (!strcmp(input, "div\n"))
            result = CMD_DIV;
        else if (!strcmp(input, "sqr\n"))
            result = CMD_SQR;
    }

    return result;
}

exit_t input_numbers(node_t **bn1, node_t **bn2)
{
    int val;
    int res = scanf("%d", &val);

    if (res == 1 && val > 0 && bn1)
    {
        int_darr_t arr = { 0 };
        *bn1 = bign_from_int(val, &arr, &res);

        if (res == ARR_NO_MEMORY)
            res = exit_no_memory;

        if ((res == exit_success) && bn2)
        {
            res = scanf("%d", &val);
            res = (res == 1 && val > 0) ? exit_success : exit_invalid_number;
        }

        if ((res == exit_success) && bn2)
        {
            *bn2 = bign_from_int(val, &arr, &res);

            if (res == ARR_NO_MEMORY)
                res = exit_no_memory;
        }

        int_darr_free(&arr);

        if (res != exit_success)
        {
            if (bn1)
                clear(bn1, 1);

            if (bn2)
                clear(bn2, 1);
        }
    }
    else
    {
        res = exit_invalid_number;
    }

    return res;
}
