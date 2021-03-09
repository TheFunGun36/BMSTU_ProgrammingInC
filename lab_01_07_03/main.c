#include <stdio.h>
#include <math.h>

#define EXIT_OK 0
#define EXIT_INVALID_INPUT -1
#define EXIT_INVALID_EPS -2
#define EXIT_INVALID_X -3

int is_equal(double value_a, double value_b);
double calculate_f(double x);
double calculate_s(double x, double e);
double abs_delta(double value1, double value2);
double rel_delta(double abs_delta, double value);

int main()
{
    double x;
    double e;
    
    if (scanf("%lf%lf", &x, &e) != 2)
        return EXIT_INVALID_INPUT;

    if (e > 1.0 || e <= 0.0 || is_equal(e, 0.0))
        return EXIT_INVALID_EPS;

    if (fabs(x) > 1.0)
        return EXIT_INVALID_X;
    
    double f_value = calculate_f(x);
    double s_value = calculate_s(x, e);
    double abs_d = abs_delta(f_value, s_value);
    double rel_d = rel_delta(abs_d, f_value);

    printf("%lf %lf %lf %lf", f_value, s_value, abs_d, rel_d);
    
    return EXIT_OK;
}

int is_equal(double value_a, double value_b)
{
    return fabs(value_a - value_b) <= 1e-10;
}

double calculate_f(double x)
{
    return atan(x);
}

double calculate_s(double x, double e)
{
    double sum = x;
    double delta_sum = e + 1.0;
    double element = x;

    for (int i = 1; delta_sum > e; i += 1)
    {
        element *= x * x;
        element *= 2 * (i - 1) + 1;
        element /= 2 * i + 1;
        element *= -1;
     
        double new_sum = sum + element;
        delta_sum = fabs(new_sum - sum);
        sum = new_sum;
    }

    return sum;
}

double abs_delta(double value1, double value2)
{
    return fabs(value1 - value2);
}

double rel_delta(double abs_delta, double value)
{
    return abs_delta / fabs(value);
}