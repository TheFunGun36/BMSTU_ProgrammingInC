#include "mylib.h"
#include <stdarg.h>
#include <inttypes.h>

int my_snprintf(char *restrict s, size_t n, const char *restrict format, ...)
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
                    {
                        int val = va_arg(vl, int);

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
                    }
                    break;
                case 'c':
                    if (converted < n)
                        s[converted] = (char)va_arg(vl, int);
                    converted++;
                    break;
                case 's':
                    {
                        char *str = va_arg(vl, char *);

                        while (*str != '\0')
                        {
                            if (converted < n)
                                s[converted] = *str;
                            converted++;
                            str++;
                        }
                    }
                    break;
                case 'o':
                    {
                        unsigned val = va_arg(vl, unsigned);
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
                    }
                    break;
            }
        }
    }

    va_end(vl);

    if (n > 0)
        s[(converted < n) ? converted : n - 1] = '\0';

    return converted;
}
