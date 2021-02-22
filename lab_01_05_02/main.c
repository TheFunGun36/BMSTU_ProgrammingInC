#include <stdio.h>

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int biggest_common_factor(int a, int b)
{
    // Using euclid's algorythm

    if (a < 0)
        a = -a;
    
    if (b < 0)
        b = -b;

    while (a != b)
    {
        if (a < b)
            swap(&a, &b);

        a -= b;
    }

    return a;
}

int main()
{
    int a, b;

    int succesfully_read = scanf("%d%d", &a, &b);

    if (succesfully_read != 2 || a == 0 || b == 0)
    {
        return -1;
    }
    else
    {
        int result = biggest_common_factor(a, b);

        printf("%d", result);
    }

    return 0;
}
