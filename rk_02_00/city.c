#include <stdio.h>
#include "city.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1

int read_struct_from_file(char *filename, City cities[], int *cities_amount)
{
    int exit_code = EXIT_SUCCESS;
    FILE *f = fopen(filename, "r");

    if (f)
    {
        int result = fscanf(f, "%d", *cities_amount);

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
                result |= fscanf(f, "%d", &cities[i].emergence_date);

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

int print_some_info(char *filename, City cities[], int *cities_amount)
{

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
