#include <stdio.h>
#include <string.h>
#include "fileio.h"
#include "arrayworks.h"
#include "errorcodes.h"

#define ARG_FILEIN 1
#define ARG_FILEOUT 2
#define ARG_FILTER 3

#define ARGC_MAX 4

int check_args(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    int exit_code = check_args(argc, argv);

    int *arr_begin = NULL, *arr_end = NULL;

    if (exit_code == EXIT_SUCCESS)
    {
        FILE *file_stream_in = fopen(argv[ARG_FILEIN], "rt");

        if (file_stream_in)
        {
            exit_code = create_array_from_file(file_stream_in, &arr_begin, &arr_end);
            fclose(file_stream_in);
        }
        else
            exit_code = EXIT_FILE_CANT_BE_OPENED;
    }

    if (exit_code == EXIT_SUCCESS && argc == ARGC_MAX)
        exit_code = filter_array(&arr_begin, &arr_end);

    if (exit_code == EXIT_SUCCESS)
        mysort(arr_begin, arr_end - arr_begin, sizeof(int), compar_ascend);

    if (exit_code == EXIT_SUCCESS)
    {
        FILE *file_stream_out = fopen(argv[ARG_FILEOUT], "wt");
        
        if (file_stream_out)
        {
            exit_code = write_array_to_file(file_stream_out, arr_begin, arr_end);
            fclose(file_stream_out);
        }
        else
            exit_code = EXIT_FILE_CANT_BE_OPENED;
    }

    safe_free(&arr_begin, &arr_end);
    
    return exit_code;
}

int check_args(int argc, char *argv[])
{
    int exit_code = EXIT_SUCCESS;

    if (argc == ARGC_MAX && strcmp(argv[ARG_FILTER], "f"))
        exit_code = EXIT_INVALID_ARGS;
    else if (argc != ARGC_MAX && argc != ARGC_MAX - 1)
        exit_code = EXIT_INVALID_ARGS_COUNT;

    return exit_code;
}
