#include <stdio.h>

int main()
{
    int seconds;

    scanf("%d", &seconds);

    int minutes = seconds / 60;
    seconds %= 60;

    int hours = minutes / 60;
    minutes %= 60;

    printf("%d %d %d", hours, minutes, seconds);

    return 0;
}
