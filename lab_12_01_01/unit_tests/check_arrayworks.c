#include <stdlib.h>
#include "arrayworks.h"
#include "check_arrayworks.h"

int is_sorted(int *arr, int sz)
{
    int result = 1;

    for (int i = 1; i < sz && result; i++)
        if (arr[i] < arr[i - 1])
            result = 0;

    return result;
}

int check_mysort()
{
    int exit_code = 0;

    {
        int arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
        int arr_sz = sizeof(arr) / sizeof(int);
        mysort(arr, arr_sz, sizeof(int), compar_ascend);
        exit_code += !is_sorted(arr, sizeof(arr) / sizeof(int));
    }

    {
        int arr[] = {1, 2, 3, 4, 5, 7, 6, 8, 9};
        int arr_sz = sizeof(arr) / sizeof(int);
        mysort(arr, arr_sz, sizeof(int), compar_ascend);
        exit_code += !is_sorted(arr, sizeof(arr) / sizeof(int));
    }

    {
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        int arr_sz = sizeof(arr) / sizeof(int);
        mysort(arr, arr_sz, sizeof(int), compar_ascend);
        exit_code += !is_sorted(arr, sizeof(arr) / sizeof(int));
    }

    {
        int arr[] = {9, -1};
        int arr_sz = sizeof(arr) / sizeof(int);
        mysort(arr, arr_sz, sizeof(int), compar_ascend);
        exit_code += !is_sorted(arr, sizeof(arr) / sizeof(int));
    }

    {
        int arr[] = {1, -9};
        int arr_sz = sizeof(arr) / sizeof(int);
        mysort(arr, arr_sz, sizeof(int), compar_ascend);
        exit_code += !is_sorted(arr, sizeof(arr) / sizeof(int));
    }

    return exit_code;
}

int arr_cmp(int *arr, int sz, int *arr_begin, int *arr_end)
{
    int result = 0;

    if (sz != arr_end - arr_begin)
        result = 1;

    int *ptr = arr_begin;
    for (int i = 0; i < sz && !result; i++)
    {
        if (arr[i] != *ptr)
            result = 1;

        ptr++;
    }

    return result;
}

int test_key(int *arr, int arr_sz, int *expect, int expect_sz)
{
    int result = 1;
    int *res_begin = malloc(expect_sz * sizeof(int));
    int *res_end = res_begin + expect_sz;

    int key_res = key(arr, arr + arr_sz, &res_begin, &res_end);

    if (key_res == 0 && res_begin != NULL && res_end != NULL)
    {
        if (!arr_cmp(expect, expect_sz, res_begin, res_end))
            result = 0;
    }

    if (res_begin != NULL)
        free(res_begin);

    return result;
}

int check_key()
{
    int exit_code = 0;

    {
        int arr[] = {4, 3, 2, 1, 5, 6, 7, 9, 8};
        int expected[] = {5, 6, 7};
        int arr_sz = sizeof(arr) / sizeof(int);
        int expected_sz = sizeof(expected) / sizeof(int);

        exit_code += test_key(arr, arr_sz, expected, expected_sz);
    }

    {
        int arr[] = {4, 3, 2, 1, 6, 9, 8};
        int expected[] = {6};
        int arr_sz = sizeof(arr) / sizeof(int);
        int expected_sz = sizeof(expected) / sizeof(int);

        exit_code += test_key(arr, arr_sz, expected, expected_sz);
    }

    {
        int arr[] = {1, 5, 6, 7, 9};
        int expected[] = {5, 6, 7};
        int arr_sz = sizeof(arr) / sizeof(int);
        int expected_sz = sizeof(expected) / sizeof(int);

        exit_code += test_key(arr, arr_sz, expected, expected_sz);
    }

    {
        int arr[] = {5, 5, 6};
        int expected[] = {5};
        int arr_sz = sizeof(arr) / sizeof(int);
        int expected_sz = sizeof(expected) / sizeof(int);

        exit_code += test_key(arr, arr_sz, expected, expected_sz);
    }

    {
        int arr[] = {5, 5, 5, 4, 7, 6};
        int arr_sz = sizeof(arr) / sizeof(int);
        exit_code += !key(arr, arr + arr_sz, NULL, NULL);
    }

    {
        int arr[] = {5, 6, 6, 6};
        int arr_sz = sizeof(arr) / sizeof(int);
        int *pb, *pe;
        exit_code += !key(arr, arr + arr_sz, &pb, &pe);
    }

    return exit_code;
}
