#include <stdio.h>
//#include <stdbool.h>
//#include <stdlib.h>
#include <math.h>

//0, if succeded
int get_point_from_user(double *x, double *y)
{
    int succesfully_scanned = scanf("%lf%lf", x, y);

    return (int)(succesfully_scanned != 2);
}

int equal(double a, double b)
{
    return fabs(a - b) < 1e-6;
}

int check_point_position(double point_x, double point_y,
double line_point1_x, double line_point1_y,
double line_point2_x, double line_point2_y)
{
    // line equation
    double line_coefficient = (line_point1_y - line_point2_y)
        / (line_point1_x - line_point2_x);

    double line_free = line_point1_y - line_coefficient * line_point1_x;

    // so now y = line_coefficient * x + line_free. Just put our point there:
    double result = line_coefficient * point_x + line_free - point_y;

    if (equal(result, 0.0))
        return 1;
    else if (result < 0.0)
        return 0;
    else
        return 2;
}

int main()
{
    // INPUT
    double point_x, point_y;

    double line_point1_x, line_point1_y;
    double line_point2_x, line_point2_y;

    if (get_point_from_user(&line_point1_x, &line_point1_y))
        return -1;

    if (get_point_from_user(&line_point2_x, &line_point2_y))
        return -1;

    if (get_point_from_user(&point_x, &point_y))
        return -1;

    // ALGORYTHM

    int result;

    if (equal(line_point1_x, line_point2_x) && equal(line_point1_y, line_point2_y))
        return -1;

    if (equal(line_point1_x, line_point2_x))
    {   
        // vertical
        if (equal(point_x, line_point1_x))
            result = 1;
        else if (point_x > line_point1_x)
            result = 2;
        result = 0;
        //return -1;
    }
    else if (equal(line_point1_y, line_point2_y))
    {
        // horizontal
        if (equal(point_y, line_point1_y))
            result = 1;
        else if (point_y < line_point1_y)
            result = 2;
        else
            result = 0;
    }
    else 
    {
        // general
        result = check_point_position(point_x, point_y,
        line_point1_x, line_point1_y,
        line_point2_x, line_point2_y);
    }

    printf("%d", result);

    return 0;
}
