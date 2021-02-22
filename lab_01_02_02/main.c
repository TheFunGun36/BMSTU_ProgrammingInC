#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*double distance(double pointa_x, double pointa_y, double pointb_x, double pointb_y)
{
    double distance_x = abs(pointa_x - pointb_x);
    double distance_y = abs(pointa_y - pointb_y);
    return sqrt(distance_x * distance_x + distance_y * distance_y); 
}*/

int main()
{
    double point1_x, point1_y;
    double point2_x, point2_y;
    double point3_x, point3_y;

    printf("info\n");

    scanf("%lf%lf", &point1_x, &point1_y);
    scanf("%lf%lf", &point2_x, &point2_y);
    scanf("%lf%lf", &point3_x, &point3_y);

    double perimeter = 0.0;

    double distance_x = abs(point1_x - point2_x);
    double distance_y = abs(point1_y - point2_y);
    perimeter += sqrt(distance_x * distance_x + distance_y + distance_y);

    distance_x = abs(point2_x - point3_x);
    distance_y = abs(point2_y - point3_y);
    perimeter += sqrt(distance_x * distance_x + distance_y + distance_y);

    distance_x = abs(point1_x - point3_x);
    distance_y = abs(point1_y - point3_y);
    perimeter += sqrt(distance_x * distance_x + distance_y + distance_y);

    /*perimeter += distance(point1_x, point1_y, point2_x, point2_y);
    perimeter += distance(point1_x, point1_y, point3_x, point3_y);
    perimeter += distance(point2_x, point2_y, point3_x, point3_y);*/

    printf("%lf\n", perimeter);
    
    return 0;
}
