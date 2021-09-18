#include <stdlib.h>
#include "fileio.h"
#include "arrayworks.h"
#include "errorcodes.h"

int count_elements(FILE *f, int *result)
{
    int exit_code = EXIT_SUCCESS;
    int counter = -1;
    int scan_result;
    int tmp;

    do
    {
        scan_result = fscanf(f, "%d", &tmp);
        counter++;
    } while (scan_result == 1);
    
    if (scan_result != EOF)
        exit_code = EXIT_INVALID_FILE_CONTENT;
    else if (counter <= 0)
        exit_code = EXIT_EMPTY_FILE;
    else
        *result = counter;

    fseek(f, 0, SEEK_SET);

    return exit_code;
}

int read_elements(FILE *f, int *arr_begin, int *arr_end)
{
    int exit_code = EXIT_SUCCESS;

    for (int *p = arr_begin; p < arr_end && exit_code == EXIT_SUCCESS; p++)
    {
        if (fscanf(f, "%d", p) != 1)
            exit_code = EXIT_INVALID_FILE_CONTENT;
    }

    return exit_code;
}

int create_array_from_file(FILE *f, int **arr_begin, int **arr_end)
{
    int elements_count;
    int exit_code = count_elements(f, &elements_count);

    if (exit_code == EXIT_SUCCESS)
    {
        int *arr = malloc(elements_count * sizeof(int));

        if (!arr)
            exit_code = EXIT_NO_MEMORY;
        else
        {
            *arr_begin = arr;
            *arr_end = arr + elements_count;
        }
    }

    if (exit_code == EXIT_SUCCESS)
        exit_code = read_elements(f, *arr_begin, *arr_end);

    if (exit_code != EXIT_SUCCESS)
        safe_free(arr_begin, arr_end);

    return exit_code;
}

int write_array_to_file(FILE *f, int *arr_begin, int *arr_end)
{
    int exit_code = EXIT_SUCCESS;

    for (int *p = arr_begin; p < arr_end - 1; p++)
    {
        if (fprintf(f, "%d ", *p) < 0)
            exit_code = EXIT_FILE_NO_ACCESS;
    }

    if (fprintf(f, "%d\n", *(arr_end - 1)) < 0)
        exit_code = EXIT_FILE_NO_ACCESS;

    return exit_code;
}
