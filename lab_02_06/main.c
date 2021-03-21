#include <stdio.h>
#include <inttypes.h>
#include <sys/time.h>

#define EXIT_OK 0
#define EXIT_ERR_INVALID_ELEMENT -1

#define ARRAY_SIZE 10000
#define TIME_MEASURE_REPETITION 500

int get_array_from_user(int *array, int array_size);
int process_1(const int *array, int array_size);
int process_2(const int *array, int array_size);
int process_3(const int *arr_begin, const int *arr_end);

int main()
{
    int array[ARRAY_SIZE];
    
    int exit_code = get_array_from_user(array, ARRAY_SIZE);

    if (exit_code == EXIT_OK)
    {
        struct timeval tv_start, tv_stop;
        long long elapsed_time;
        long long sum1 = 0, sum2 = 0, sum3 = 0;

        printf("Подождите, ведётся процесс тестирования алгоритмов . . .");
        for (int i = 0; i < TIME_MEASURE_REPETITION; i++)
        {
            // Process 1:
            gettimeofday(&tv_start, NULL);
            process_1(array, ARRAY_SIZE);
            gettimeofday(&tv_stop, NULL);

            elapsed_time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000ll;
            elapsed_time += (tv_stop.tv_usec - tv_start.tv_usec);
            sum1 += elapsed_time;

            // Process 2:
            gettimeofday(&tv_start, NULL);
            process_2(array, ARRAY_SIZE);
            gettimeofday(&tv_stop, NULL);

            elapsed_time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000ll;
            elapsed_time += (tv_stop.tv_usec - tv_start.tv_usec);
            sum2 += elapsed_time;

            // Process 3:
            int *array_end = array + ARRAY_SIZE;
            gettimeofday(&tv_start, NULL);
            process_3(array, array_end);
            gettimeofday(&tv_stop, NULL);

            elapsed_time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000ll;
            elapsed_time += (tv_stop.tv_usec - tv_start.tv_usec);
            sum3 += elapsed_time;
        }

        printf("\rИтоги тестирования:                                     \n");
        printf("  Процесс 1 ( a[i] ): %lld мс\n", sum1/TIME_MEASURE_REPETITION);
        printf("  Процесс 2 ( *(a + i) ): %lld мс\n", sum2/TIME_MEASURE_REPETITION);
        printf("  Процесс 3 ( *a ): %lld мс\n", sum3/TIME_MEASURE_REPETITION);
    }
    else if (exit_code & EXIT_ERR_INVALID_ELEMENT)
    {
        int element_position = exit_code & ~EXIT_ERR_INVALID_ELEMENT;
        printf("Error: invalid element in position %d.\n", element_position);
        exit_code = EXIT_ERR_INVALID_ELEMENT;
    }

    return exit_code;
}

int get_array_from_user(int *array, int array_size)
{
    for (int i = 0; i < array_size; i++)
    {
        int result = scanf("%d", &array[i]);
        
        if (result != 1)
            return EXIT_ERR_INVALID_ELEMENT | i;
    }

    return EXIT_OK;
}

int process_1(const int *array, int array_size)
{
    int result = array_size;
    int j;

    for (int i = 0; i < array_size - 1; i++)
    {
        j = i + 1;

        while (array[j] != array[i] && j < array_size)
            j++;

        if (j != array_size)
            result--;
    }

    return result;
}

int process_2(const int *array, int array_size)
{
    int result = array_size;
    int j;

    for (int i = 0; i < array_size - 1; i++)
    {
        j = i + 1;

        while (*(array + j) != *(array + i) && j < array_size)
            j++;

        if (j != array_size)
            result--;
    }

    return result;
}

int process_3(const int *arr_begin, const int *arr_end)
{
    int result = arr_end - arr_begin;
    const int *temp_pointer;

    while (arr_begin < arr_end - 1)
    {
        temp_pointer = arr_begin + 1;

        while (*temp_pointer != *arr_begin && temp_pointer < arr_end)
            temp_pointer++;

        if (temp_pointer != arr_end)
            result--;

        arr_begin++;
    }

    return result;
}