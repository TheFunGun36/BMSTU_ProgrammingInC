#include <stdio.h>
#include "file_works.h"

#define EXIT_INVALID_ARG_AMOUNT -10
#define EXIT_INVALID_FILE_SIZE -11
#define EXIT_CMD_NOT_FOUND -12

void print_error_message(int exit_code, int argc, char *argv[])
{
    switch (exit_code)
    {
    case EXIT_INVALID_FILE_SIZE:
        printf("Error: file size should be an integer");
        break;

    case EXIT_INVALID_ARG_AMOUNT:
        printf("Error: invalid arguments amount. Got %d, expected 3\n", argc);
        break;

    case EXIT_CMD_NOT_FOUND:
        printf("Error: first argument should be 'c', 'p' or 's', not %s\n", argv[1]);
        break;

    case EXIT_NO_FILE:
        printf("Error: file \"%s\" not found", argv[2]);
        break;

    case EXIT_NO_ACCESS:
        printf("Error: cant read/write to file (no access?)");
        break;
    }
}

int main(int argc, char *argv[])
{
    int exit_code = EXIT_SUCCESS;

    if (argc != 3)
    {
        exit_code = EXIT_INVALID_ARG_AMOUNT;
    }
    else if (argv[1][1] != '\0')
    {
        exit_code = EXIT_CMD_NOT_FOUND;
    }
    else
    {
        switch (argv[1][0])
        {
        case 'c':
            {
                int n;

                setbuf(stdin, NULL);

                printf("Enter file size\n>");

                if (scanf("%d", &n) != 1)
                    exit_code = EXIT_INVALID_FILE_SIZE;
                else
                    exit_code = create_file(argv[2], n);
            }
            break;

        case 'p':
            exit_code = print_file_content(argv[2]);
            break;

        case 's':
            exit_code = sort_file_content(argv[2]);
            break;

        default:
            exit_code = EXIT_CMD_NOT_FOUND;
        }
    }

    print_error_message(exit_code, argc, argv);

    return exit_code;
}
