#include <stdio.h>
#include <string.h>
#include "goods.h"

#define EXIT_INVALID_ARGS 53

int main(int argc, char *argv[])
{
    int exit_code = SUCCESS;

    if (!((argc == 3 && strcmp(argv[1], "at")) || (argc == 4 && (strcmp(argv[1], "st") || strcmp(argv[1], "ft")))))
        return EXIT_INVALID_ARGS;

    switch (argv[1][0])
    {
    case 's':

        break;
    }

    return exit_code;
}
