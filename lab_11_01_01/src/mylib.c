#include "mylib.h"
#include <stdarg.h>
#include <inttypes.h>

static int put_int(char *s, size_t n, int val, int converted)
{
    if (val < 0)
    {
        if (converted < n)
            s[converted] = '-';
        converted++;
        val = -val;
    }

    int dgts = 0;

    for (int v = val; v > 0; v /= 10)
        dgts++;

    dgts = dgts ? dgts : 1;

    for (int i = 1; i <= dgts; i++)
    {
        char dgt = '0' + val % 10;

        if (converted + dgts - i < n)
            s[converted + dgts - i] = dgt;

        val /= 10;
    }

    converted += dgts;

    return converted;
}

static int put_oct(char *s, size_t n, unsigned val, int converted)
{
    uint64_t mask = 0x7;
    int shifts = 0;

    while (3 * (shifts + 1) < sizeof(unsigned) * 8)
    {
        shifts++;
        mask <<= 3;
    }

    while (!(mask & val) && mask)
    {
        shifts--;
        mask >>= 3;
    }

    if (mask)
    {
        while (mask)
        {
            int c = '0' + ((val & mask) >> (3 * shifts));
            if (converted < n)
                s[converted] = c;
            converted++;
            mask >>= 3;
            shifts--;
        }
    }
    else
    {
        if (converted < n)
            s[converted] = '0';
        converted++;
    }

    return converted;
}

static int put_str(char *s, size_t n, char *str, int converted)
{
    while (*str != '\0')
    {
        if (converted < n)
            s[converted] = *str;
        converted++;
        str++;
    }

    return converted;
}

static int put_chr(char *s, size_t n, char val, int converted)
{
    if (converted < n)
        s[converted] = val;
    return ++converted;
}

int my_snprintf(char *s, size_t n, const char *format, ...)
{
    va_list vl;
    size_t converted = 0;

    va_start(vl, format);

    while (*format != '\0')
    {
        if (*format != '%')
        {
            if (converted < n)
                s[converted] = *format;
            format++;
            converted++;
        }
        else
        {
            format++;
            switch (*format++)
            {
                case 'd':
                    converted = put_int(s, n, va_arg(vl, int), converted);
                    break;
                case 'c':
                    converted = put_chr(s, n, (char)va_arg(vl, int), converted);
                    break;
                case 's':
                    converted = put_str(s, n, va_arg(vl, char *), converted);
                    break;
                case 'o':
                    converted = put_oct(s, n, va_arg(vl, unsigned), converted);
                    break;
                default:
                    {
                        // yooo, im memory leak!
                        int *a = malloc(sizeof(int));
                        // printing junk!
                        printf("%d", a);
                    }
            }
        }
    }

    va_end(vl);

    if (n > 0)
        s[(converted < n) ? converted : n - 1] = '\0';

    return converted;
}
