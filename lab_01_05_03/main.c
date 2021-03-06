#include <stdio.h>

#define EXIT_OK 0
#define EXIT_ERR_INVALID_INPUT -1
#define EXIT_ERR_NOT_POSITIVE_FIRST_NUMBER -2
#define EXIT_ERR_NOT_POSITIVE_SECOND_NUMBER -3

int read_two_positive_numbers(int *a, int *b);
void swap(int *a, int *b);
int biggest_common_factor(int a, int b);

int main()
{
    int first_number, second_number;

    int exit_code = read_two_positive_numbers(&first_number, &second_number);

    if (exit_code != EXIT_OK)
        return exit_code;

    int result = biggest_common_factor(first_number, second_number);

    printf("%d", result);

    return EXIT_OK;
}

int read_two_positive_numbers(int *a, int *b)
{
    if (scanf("%d%d", a, b) != 2)
        return EXIT_ERR_INVALID_INPUT;

    if (*a <= 0)
        return EXIT_ERR_NOT_POSITIVE_FIRST_NUMBER;
    if (*b <= 0)
        return EXIT_ERR_NOT_POSITIVE_SECOND_NUMBER;

    return EXIT_OK;
}

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int biggest_common_factor(int a, int b)
{
    // Using euclid's algorythm

    while (a != b)
    {
        if (a < b)
            swap(&a, &b);

        a -= b;
    }

    return a;
}
