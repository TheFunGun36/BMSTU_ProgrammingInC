#include <stdio.h>

int main()
{
    double r1, r2, r3;
    
    scanf("%lf%lf%lf", &r1, &r2, &r3);

    double resistance = (r1 * r2 * r3) / (r1 * r2 + r2 * r3 + r1 * r3);

    printf("%f", resistance);

    return 0;
}
