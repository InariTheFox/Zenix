#include "cpu.h"
#include "ctype.h"
#include "stdarg.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int print_format(char *str, const char *format, va_list arg);

int vsprintf(char *str, const char *format, va_list arg)
{
    int i;

    i = print_format(str, format, arg);
    //*str = 0;

    return i;
}

int sprintf(char *str, const char *format, ...)
{
    va_list arg;
    int     i;

    va_start(arg, format);
    i = print_format(str, format, arg);
    //*str = 0;
    va_end(arg);

    return i;
}

int print_format(char *str, const char *format, va_list arg)
{
    arg;
    char c;
    int  i;

    i = 0;

    c = *format++;

    while (c != '\0')
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
                    char *d = 0;

                    itoa(v, d, 10);

                    while((c = *d++))
                    {
                        *str++ = c;
                    }

                    break;
                case 's':
                    char *s = va_arg(arg, char *);

                    while((c = *s++))
                    {
                        *str++ = c;
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