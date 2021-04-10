#include <stdio.h>

#define OK 0
#define INVALID_INPUT -1
#define NEGATIVE_INPUT -2

int get_number_from_user(int *number)
{
    if (scanf("%d", number) != 1)
        return INVALID_INPUT;

    if (*number <= 0)
        return NEGATIVE_INPUT;

    return OK;
}

int find_largest_digit(int number)
{
    int max_digit = 0;
    
    while (number > 0)
    {
        int digit = number % 10;
        number /= 10;

        if (digit > max_digit)
            max_digit = digit;
    }

    return max_digit;
}

void print_number(int number)
{
    printf("%d\n", number);
}

int main()
{
    int number;
    int exit_code = get_number_from_user(&number);

    if (exit_code != OK)
        return exit_code;

    int max_digit = find_largest_digit(number);
    print_number(max_digit);

    return exit_code;
}