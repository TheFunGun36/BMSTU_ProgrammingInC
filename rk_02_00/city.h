#ifndef CITY_H
#define CITY_H

#define MAX_STRING_SIZE 100

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1

typedef struct City {
    char name[MAX_STRING_SIZE];
    char region[MAX_STRING_SIZE];
    char fed_okr[MAX_STRING_SIZE];
    int people_amount;
    int emergence_date;
} City;

int read_struct_from_file(char *filename, City cities[], int *cities_amount);
int print_some_info(char *filename, City cities[], int *cities_amount);
//int print_foreach(char *filename, City cities[], int cities_amount);

#endif
