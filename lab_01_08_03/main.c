#include <stdio.h>


void swap_bytes(unsigned int *value, int index1, int index2)
{
    //index1 = 7 - index1;
    //index2 = 7 - index2;
    int v1 = (*value & (1 << index1)) >> index1;
    int v2 = (*value & (1 << index2)) >> index2;
    *value &= ~(1 << index1 | 1 << index2);
    *value |= v1 << index2;
    *value |= v2 << index1;
}

void print_bin(unsigned int value)
{
    const int bits_last_index = 31;
    char str[bits_last_index + 2];
    str[bits_last_index + 1] = '\0';

    for (int i = 0; i <= bits_last_index; i += 1)
        str[i] = (value & (1 << (bits_last_index - i))) ? '1' : '0';
    
    printf("%s", str);
}

unsigned int encrypt(unsigned int value)
{
    const int bits_last_index = 31;
    
    for (int i = 0; i < bits_last_index; i += 2)
    {
        swap_bytes(&value, i, i + 1);
    }

    return value;
}

int main()
{
    unsigned int number;

    if (scanf("%d", &number) != 1)
        return -1;

    number = encrypt(number);
    print_bin(number);
    
    return 0;
}