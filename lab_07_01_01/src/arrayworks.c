#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "arrayworks.h"
#include "errorcodes.h"

void mysort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *))
{
    char *lower_last_swap = (char *)base;
    char *higher_last_swap = (char *)base + (nitems - 1) * size;
    char *swap_buf = malloc(size);

    if (swap_buf)
    {
        uint8_t should_ascend = 1;
        char *tmp_last_swap = NULL;

        do
        {
            tmp_last_swap = NULL;

            if (should_ascend)
            {
                should_ascend = 0;

                for (char *p = lower_last_swap; p < higher_last_swap; p += size)
                {
                    if (compar(p, p + size) > 0)
                    {
                        memcpy(swap_buf, p, size);
                        memcpy(p, p + size, size);
                        memcpy(p + size, swap_buf, size);

                        tmp_last_swap = p;
                    }
                }

                higher_last_swap = tmp_last_swap;
            }
            else
            {
                should_ascend = 1;

                for (char *p = higher_last_swap; p > lower_last_swap; p -= size)
                {
                    if (compar(p - size, p) > 0)
                    {
                        memcpy(swap_buf, p, size);
                        memcpy(p, p - size, size);
                        memcpy(p - size, swap_buf, size);

                        tmp_last_swap = p;
                    }
                }

                lower_last_swap = tmp_last_swap;
            }
        } while (tmp_last_swap != NULL);

        free(swap_buf);
    }
}

void find_min_max_element(const int *arr_begin, const int *arr_end, const int **min, const int **max)
{
    *min = arr_begin;
    *max = arr_begin;

    for (const int *p = arr_begin + 1; p < arr_end; p++)
    {
        if (*p > **max)
            *max = p;
        if (*p < **min)
            *min = p;
    }
}

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    int exit_code = EXIT_SUCCESS;

    if (pb_src == NULL || pe_src == NULL || pb_dst == NULL || pe_dst == NULL)
        exit_code = EXIT_NULLPTR_INPUT;

    const int *arr_part_begin, *arr_part_end;
    find_min_max_element(pb_src, pe_src, &arr_part_begin, &arr_part_end);

    if (arr_part_begin > arr_part_end)
    {
        const int *tmp = arr_part_end;
        arr_part_end = arr_part_begin;
        arr_part_begin = tmp;
    }

    arr_part_begin++;

    if (arr_part_end - arr_part_begin <= 0)
        exit_code = EXIT_EMPTY_RESULT_ARRAY;
    else
    {
        int result_arr_length = arr_part_end - arr_part_begin;
        *pb_dst = malloc(result_arr_length * sizeof(int));
        *pe_dst = *pb_dst + result_arr_length;

        if (*pb_dst == NULL)
            exit_code = EXIT_NO_MEMORY;
        else
            memcpy(*pb_dst, arr_part_begin, result_arr_length * sizeof(int));
    }

    return exit_code;
}

int filter_array(int **arr_begin, int **arr_end)
{
    int *new_arr_begin, *new_arr_end;

    int exit_code = key(*arr_begin, *arr_end, &new_arr_begin, &new_arr_end);

    if (exit_code == EXIT_SUCCESS)
    {
        safe_free(arr_begin, arr_end);
        *arr_begin = new_arr_begin;
        *arr_end = new_arr_end;
    }

    return exit_code;
}

void safe_free(int **arr_begin, int **arr_end)
{
    if (*arr_begin != NULL)
    {
        free(*arr_begin);
        *arr_begin = NULL;
        *arr_end = NULL;
    }
}

int compar_ascend(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}
