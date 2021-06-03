#include <stdio.h>
#include "city.h"

#define MAX_CITIES_AMOUNT 1300

int main()
{
    City cities[MAX_CITIES_AMOUNT];
    int cities_amount;

    int exit_code = read_struct_from_file("in.txt", cities, &cities_amount);

    if (exit_code == EXIT_FAILURE)
        return exit_code;

    exit_code = print_some_info("out.txt", cities, &cities_amount);

    return exit_code;
}
