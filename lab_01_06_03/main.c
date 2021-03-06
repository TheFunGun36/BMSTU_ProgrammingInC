#include <stdio.h>
#include <math.h>

#define RET_OK 0
#define RET_INVALID_INPUT -1

#define EXIT_OK 0
#define EXIT_ERR_INV_INPUT_POINT -1
#define EXIT_ERR_INV_INPUT_LINE_POINT1 -2
#define EXIT_ERR_INV_INPUT_LINE_POINT2 -3
#define EXIT_ERR_IMPOSSIBLE_LINE -4

#define POINT_ABOVE 0
#define POINT_ON 1
#define POINT_UNDER 2

int get_point_from_user(double *x, double *y);
int is_equal(double a, double b);
int check_point_position(double point_x, double point_y,
double line_point1_x, double line_point1_y,
double line_point2_x, double line_point2_y);

int main()
{
    // INPUT
    double point_x, point_y;

    double line_point1_x, line_point1_y;
    double line_point2_x, line_point2_y;

    if (get_point_from_user(&line_point1_x, &line_point1_y))
        return EXIT_ERR_INV_INPUT_LINE_POINT1;
    if (get_point_from_user(&line_point2_x, &line_point2_y))
        return EXIT_ERR_INV_INPUT_LINE_POINT1;
    if (get_point_from_user(&point_x, &point_y))
        return EXIT_ERR_INV_INPUT_POINT;

    // ALGORYTHM

    int result;

    if (is_equal(line_point1_x, line_point2_x) && is_equal(line_point1_y, line_point2_y))
        return EXIT_ERR_IMPOSSIBLE_LINE;

    if (is_equal(line_point1_x, line_point2_x))
    {   
        // vertical line
        if (is_equal(point_x, line_point1_x))
            result = POINT_ON;
        else if (point_x > line_point1_x)
            result = POINT_UNDER;
        else
            result = POINT_ABOVE;
    }
    else if (is_equal(line_point1_y, line_point2_y))
    {
        // horizontal line
        if (is_equal(point_y, line_point1_y))
            result = POINT_ON;
        else if (point_y < line_point1_y)
            result = POINT_UNDER;
        else
            result = POINT_ABOVE;
    }
    else 
    {
        // general case (any other line)
        result = check_point_position(point_x, point_y,
        line_point1_x, line_point1_y,
        line_point2_x, line_point2_y);
    }

    // OUTPUT

    printf("%d", result);

    return EXIT_OK;
}

int get_point_from_user(double *x, double *y)
{
    if (scanf("%lf%lf", x, y) != 2)
        return RET_INVALID_INPUT;

    return RET_OK;
}

int is_equal(double a, double b)
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

    if (is_equal(result, 0.0))
        return POINT_ON;
    else if (result < 0.0)
        return POINT_ABOVE;
    else
        return POINT_UNDER;
}