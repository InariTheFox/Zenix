#include "ctype.h"
#include "stdarg.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int print_format(char *str, const char *format, va_list arg);

int vsprintf(char *str, const char *format, va_list arg)
{
    int i;

    i = print_format(str, format, arg);

    return i;
}

int sprintf(char *str, const char *format, ...)
{
    va_list arg;
    int     i;

    va_start(arg, format);
    i = print_format(str, format, arg);
    va_end(arg);

    return i;
}

int print_format(char *str, const char *format, va_list arg)
{
    char  c;
    char *s;
    int   i;

    i = 0;

    c = *format++;

    while (c != 0)
    {
        if (c == '%')
        {
            c = *format++;

            if (c == '%')
            {
                continue;
            }

            switch (c)
            {
            case 'd':
                int v = va_arg(arg, int);
                str = itoa(v, str, 10);

                break;
            case 'l':
                long int l = va_arg(arg, long int);
                str = ltoa(l, str, 10);

                break;
            case 'x':
                *str++ = '0';
                *str++ = 'x';

                unsigned int u = va_arg(arg, unsigned int);
                str = utoa(u, str, 16);

                break;
            case 'u':
                u = va_arg(arg, unsigned int);
                str = utoa(u, str, 10);

                break;
            case 's':
                s = va_arg(arg, char *);

                while ((c = *s++))
                {
                    *str++ = c;
                    i++;
                }

            default:
                break;
            }
        }
        else
        {
            *str++ = c;
            i++;
        }

        c = *format++;
    }

    ++*str = 0;
    i++;

    return i;
}