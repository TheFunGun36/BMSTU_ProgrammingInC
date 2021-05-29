#include <stdio.h>
#include "city.h"

int read_struct_from_file(char *filename, City cities[], int *cities_amount)
{
    int exit_code = EXIT_SUCCESS;
    FILE *f = fopen(filename, "r");

    if (f)
    {
        int result = fscanf(f, "%d", cities_amount);
        fgetc(f);

        if (result != 1 || *cities_amount <= 0)
            exit_code = EXIT_FAILURE;

        if (exit_code == EXIT_SUCCESS)
        {
            for (int i = 0; i < *cities_amount && exit_code == EXIT_SUCCESS; i++)
            {
                fgets(cities[i].name, MAX_STRING_SIZE, f);
                fgets(cities[i].region, MAX_STRING_SIZE, f);
                fgets(cities[i].fed_okr, MAX_STRING_SIZE, f);

                result = fscanf(f, "%d", &cities[i].people_amount);
                fgetc(f);
                result |= fscanf(f, "%d", &cities[i].emergence_date);
                fgetc(f);

                if (feof(f) || ferror(f))
                    exit_code = EXIT_FAILURE;
            }
        }

        fclose(f);
    }
    else
        exit_code = EXIT_FAILURE;

    return exit_code;
}

int count_avg_people_amount(City cities[], int cities_amount)
{
    int sum = 0;

    for (int i = 0; i < cities_amount; i++)
    {
        sum += cities[i].people_amount;
    }

    return sum / cities_amount;
}

int count_ss(char *str)
{
    int counter = 0;

    while (*str != '\0')
    {
        counter += *str == 's' || *str == 'S';
        str++;
    }

    return counter;
}

int count_sm_ss(char *str)
{
    int counter = 0;

    while (*str != '\0')
    {
        counter += *str == 's';
        str++;
    }

    return counter;
}

int get_best_index_b(City cities[], int cities_amount)
{
    int best_index = 0;
    int ss = count_ss(cities[0].name);

    for (int i = 1; i < cities_amount; i++)
    {
        int cur_ss = count_ss(cities[i].name);
        if (cur_ss > ss)
        {
            best_index = i;
            ss = cur_ss;
        }
        else if (cur_ss == ss)
        {
            int a = count_sm_ss(cities[best_index].name);
            int b = count_sm_ss(cities[i].name);

            if (b < a)
            {
                best_index = i;
                ss = cur_ss;
            }
        }
    }

    return best_index;
}

int print_some_info(char *filename, City cities[], int *cities_amount)
{
    int exit_code = EXIT_SUCCESS;

    int p_a = count_avg_people_amount(cities, *cities_amount);
    int p_b = cities[get_best_index_b(cities, *cities_amount)].emergence_date;

    FILE *f = fopen(filename, "w");

    if (f)
    {
        int result = fprintf(f, "%d\n", p_a);

        if (result > 0)
            result = fprintf(f, "%d", p_b);

        if (result <= 0)
            exit_code = EXIT_FAILURE;

        fclose(f);
    }
    else
        exit_code = EXIT_FAILURE;

    return exit_code;
}

/*int print_foreach(char *filename, City cities[], int cities_amount)
{
    int exit_code = EXIT_SUCCESS;
    FILE *f = fopen(filename, "w");

    if (f)
    {
        for (int i = 0; i < cities_amount; i++)
        {

        }

        fclose(f);
    }
    else
        exit_code = EXIT_FAILURE;

    return exit_code;
}*/
