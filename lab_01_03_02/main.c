#include <stdio.h>

int main()
{
    float r1, r2, r3;
    
    scanf("%f%f%f", &r1, &r2, &r3);

    float resistance = (r1 * r2 * r3) / (r1 * r2 + r2 * r3 + r1 * r3);

    printf("%f", resistance);

    return 0;
}
