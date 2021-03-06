#include <stdio.h>

#define EXIT_OK 0
#define EXIT_INVALID_INPUT -1

#define BITS_AMOUNT 32

void swap_bytes(unsigned int *value, int index1, int index2);
void print_bin(unsigned int value);
unsigned int encrypt(unsigned int value);

int main()
{
    unsigned int number;

    if (scanf("%ud", &number) != 1)
    {
        printf("Error: incorrect input");
        return EXIT_INVALID_INPUT;
    }

    number = encrypt(number);
    print_bin(number);
    
    return EXIT_OK;
}

void swap_bytes(unsigned int *value, int index1, int index2)
{
    int v1 = (*value & (1 << index1)) >> index1;
    int v2 = (*value & (1 << index2)) >> index2;
    *value &= ~(1 << index1 | 1 << index2);
    *value |= v1 << index2;
    *value |= v2 << index1;
}

void print_bin(unsigned int value)
{
    printf("Result: ");

    for (int i = 0; i < BITS_AMOUNT; i += 1)
        printf("%d", (value & (1 << (BITS_AMOUNT - 1 - i))) != 0);
}

unsigned int encrypt(unsigned int value)
{
    const int bits_last_index = 31;
    
    for (int i = 0; i < bits_last_index; i += 2)
        swap_bytes(&value, i, i + 1);

    return value;
}