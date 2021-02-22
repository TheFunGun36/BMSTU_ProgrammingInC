#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double point1_x, point1_y;
    double point2_x, point2_y;
    double point3_x, point3_y;

    scanf("%lf%lf", &point1_x, &point1_y);
    scanf("%lf%lf", &point2_x, &point2_y);
    scanf("%lf%lf", &point3_x, &point3_y);

    double side1, side2, side3;

    double distance_x = point1_x - point2_x;
    double distance_y = point1_y - point2_y;
    side1 = sqrt(distance_x * distance_x + distance_y * distance_y);

    distance_x = point2_x - point3_x;
    distance_y = point2_y - point3_y;
    side2 = sqrt(distance_x * distance_x + distance_y * distance_y);

    distance_x = point1_x - point3_x;
    distance_y = point1_y - point3_y;
    side3 = sqrt(distance_x * distance_x + distance_y * distance_y);

    double perimeter = side1 + side2 + side3;

    printf("%lf\n", perimeter);
    
    return 0;
}
