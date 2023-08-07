#include "ctype.h"
#include "stdarg.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"

int print_format(char *str, const char *format, va_list arg);

int vsprintf(char *str, const char *format, va_list arg)
{
    int i;

    i = print_format(&str, format, arg);
    *str = 0;

    return i;
}

int sprintf(char *str, const char *format, ...)
{
    va_list arg;
    int     i;

    va_start(arg, format);
    i = print_format(&str, format, arg);
    *str = 0;
    va_end(arg);

    return i;
}

int print_format(char *str, const char *format, va_list arg)
{
    char        c, radix;
    int         i, length;
    const char *ptr;
    boolean     lower_case;

    i = 0;

    while (c = *format++)
    {
        if (c == '%')
        {
            c = *format++;

            if (c == '%')
            {
                continue;
            }

            if (isdigit(c))
            {
            }

            if (islower(c))
            {
                c = toupper(c);
                lower_case = true;
            } else
            {
                lower_case = false;
            }

            switch (c)
            {
            case 'C':
                c = va_arg(arg, char);
                *str = c;
                str++;
                i++;
                break;
            case 'P':

                break;
            case 'S':
                ptr = va_arg(arg, const char *);
                length = strlen(ptr);

                while (c = *ptr)
                {
                    *str = c;
                    str++;
                    ptr++;
                }

                break;
            case 'D':
            case 'I':
                radix = 10;
                break;
            case 'O':
                radix = 8;
                break;
            case 'X':
                radix = 16;
                break;
            default:
                *str = c;
                str++;
                i++;
                break;
            }
        } else
        {
            *str = c;
            str++;
        }
    }

    return i;
}