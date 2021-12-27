#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "fileio.h"
#include "errorcodes.h"

#define ARG_FILEIN 1
#define ARG_FILEOUT 2
#define ARG_FILTER 3

#define ARGC_MAX 4

int filter_array(int **arr_begin, int **arr_end, void *handle);
int check_args(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    void *handle = dlopen("./arrayworks.dll", RTLD_LAZY);
    if (!handle) {
        fputs (dlerror(), stderr);
        exit(1);
    }
    void (*safe_free)(int **, int **) = dlsym(handle, "safe_free");

    int exit_code = check_args(argc, argv);

    int *arr_begin = NULL, *arr_end = NULL;

    if (exit_code == EXIT_SUCCESS)
    {
        FILE *file_stream_in = fopen(argv[ARG_FILEIN], "rt");

        if (file_stream_in)
        {
            exit_code = create_array_from_file(file_stream_in, &arr_begin, &arr_end, safe_free);
            fclose(file_stream_in);
        }
        else
        {
            exit_code = EXIT_FILE_CANT_BE_OPENED;
        }
    }

    if (exit_code == EXIT_SUCCESS && argc == ARGC_MAX)
    {
        exit_code = filter_array(&arr_begin, &arr_end, handle);
    }

    if (exit_code == EXIT_SUCCESS)
    {
        void (*mysort)(void *, size_t, size_t, int (*)(void*, void*)) = dlsym(handle, "mysort");
        mysort(arr_begin, arr_end - arr_begin, sizeof(int), dlsym(handle, "compar_ascend"));
    }

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

int filter_array(int **arr_begin, int **arr_end, void *handle)
{
    int exit_code = EXIT_SUCCESS;
    int *new_arr_begin;
    int *new_arr_end;

    int (*find_min_max_element)(int *, int *, const int **, const int **) = dlsym(handle, "find_min_max_element");
    void (*swap_constptr)(const void **, const void **) = dlsym(handle, "swap_constptr");
    int (*key)(const int *, const int *, int **, int **) = dlsym(handle, "key");

    find_min_max_element(*arr_begin, *arr_end, (const int **)&new_arr_begin, (const int **)&new_arr_end);

    if (new_arr_begin > new_arr_end)
        swap_constptr((const void**)&new_arr_begin, (const void**)&new_arr_end);
        
    int result_arr_length = new_arr_end - new_arr_begin - 1;

    if (result_arr_length > 0)
    {
        new_arr_begin = malloc(result_arr_length * sizeof(int));

        if (new_arr_begin)
        {
            new_arr_end = new_arr_begin + result_arr_length;
            exit_code = key(*arr_begin, *arr_end, &new_arr_begin, &new_arr_end);
        }
        else
        {
            exit_code = EXIT_NO_MEMORY;
        }

        if (exit_code == EXIT_SUCCESS)
        {
            void (*safe_free)(int **, int **) = dlsym(handle, "safe_free");
            safe_free(arr_begin, arr_end);
            *arr_begin = new_arr_begin;
            *arr_end = new_arr_end;
        }
    }
    else
    {
        exit_code = EXIT_EMPTY_RESULT_ARRAY;
    }

    return exit_code;
}