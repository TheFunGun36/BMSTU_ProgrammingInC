#include <stdlib.h>
#include <time.h>
#include "file_works.h"

int get_number_by_pos(FILE *f, int position, int *value)
{
    if (!f)
        return EXIT_NO_FILE;

    fseek(f, position * sizeof(int), SEEK_SET);

    if (fread(value, sizeof(int), 1, f) != 1)
        return EXIT_NO_ACCESS;

    return EXIT_SUCCESS;
}

int put_number_by_pos(FILE *f, int position, int value)
{
    if (!f)
        return EXIT_NO_FILE;

    fseek(f, position * sizeof(int), SEEK_SET);

    if (fwrite(&value, sizeof(int), 1, f) != 1)
        return EXIT_NO_ACCESS;

    return EXIT_SUCCESS;
}

int create_file(char *filename, int n)
{
    FILE *f = fopen(filename, "w");

    if (!f)
        return EXIT_NO_ACCESS;

    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        int v = rand() % 100;
        fwrite(&v, sizeof(int), 1, f);
    }

    fclose(f);

    return EXIT_SUCCESS;
}

int print_file_content(char *filename)
{
    FILE *f = fopen(filename, "r");

    if (!f)
        return EXIT_NO_ACCESS;

    int v;
    int result = fread(&v, sizeof(int), 1, f);

    if (result == 1)
    {
        do
        {
            printf("%d ", v);
            result = fread(&v, sizeof(int), 1, f);
        }
        while (result == 1);
    }
    else
    {
        if (!feof(f))
            return EXIT_NO_ACCESS;
        else
            return EXIT_EMPTY_FILE;
    }

    fclose(f);

    return EXIT_SUCCESS;
}

int swap_to_ascend(FILE *f, int first, int second)
{
    int first_val;
    int second_val;
    int res = get_number_by_pos(f, first, &first_val);
    res |= get_number_by_pos(f, second, &second_val);

    if (res == EXIT_SUCCESS)
    {
        if (first_val > second_val)
        {
            res |= put_number_by_pos(f, first, second_val);
            res |= put_number_by_pos(f, second, first_val);
        }
    }

    return res;
}

int sort_file_content(char *filename)
{
    FILE *f = fopen(filename, "r+");

    if (!f)
        return EXIT_NO_ACCESS;

    fseek(f, 0, SEEK_END);
    int array_size = ftell(f) / sizeof(int);
    fseek(f, 0, SEEK_CUR);

    for (int i = 0; i < array_size; i++)
    {
        for (int j = i + 1; j < array_size; j++)
        {
            int res = swap_to_ascend(f, i, j);

            if (res != EXIT_SUCCESS)
                return res;
        }
    }

    fclose(f);

    return EXIT_SUCCESS;
}
