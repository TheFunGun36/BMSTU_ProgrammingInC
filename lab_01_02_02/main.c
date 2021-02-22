#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    float point1_x, point1_y;
    float point2_x, point2_y;
    float point3_x, point3_y;

    printf("info\n");

    scanf("%lf%lf", &point1_x, &point1_y);
    scanf("%lf%lf", &point2_x, &point2_y);
    scanf("%lf%lf", &point3_x, &point3_y);

    float perimeter = 0.0f;

    float distance_x = abs(point1_x - point2_x);
    float distance_y = abs(point1_y - point2_y);
    perimeter += sqrt(distance_x * distance_x + distance_y * distance_y);

    distance_x = abs(point2_x - point3_x);
    distance_y = abs(point2_y - point3_y);
    perimeter += sqrt(distance_x * distance_x + distance_y * distance_y);

    distance_x = abs(point1_x - point3_x);
    distance_y = abs(point1_y - point3_y);
    perimeter += sqrt(distance_x * distance_x + distance_y * distance_y);

    printf("%lf\n", perimeter);
    
    return 0;
}
