#include <stdio.h>
#include <math.h>

int equal(double value_a, double value_b)
{
    return fabs(value_a - value_b) <= 1e-10;
}

double calculate_f(double x)
{
    return atan(x);
}

double calculate_s(double x, double e)
{
    double sum = 0.0;
    double delta_sum = e + 1.0;
    int odd_num_counter = 1;
    int sign = 1;

    for (int i = 0; delta_sum > e; i += 1)
    {
        double element = sign * pow(x, (double)odd_num_counter) / (double)odd_num_counter;

        odd_num_counter += 2;
        sign *= -1;
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

int main()
{
    double x;
    double e;
    
    if (scanf("%lf%lf", &x, &e) != 2)
        return -1;

    if (e > 1.0 || e <= 0.0 || equal(e, 0.0))
        return -2;

    if (fabs(x) > 1.0)
        return -3;
    
    double f_value = calculate_f(x);
    double s_value = calculate_s(x, e);
    double abs_d = abs_delta(f_value, s_value);
    double rel_d = rel_delta(abs_d, f_value);

    printf("%lf %lf %lf %lf", f_value, s_value, abs_d, rel_d);
    
    return 0;
}