#include "stdio.h"
#include "cpu.h"

char *gets(char *str)
{
    int  len = 0;
    char c, *s;

    s = str;
    *str = 0;

    c = inb(1);
    do
    {
        if (c == '\r' || c == '\n' || c == 0)
        {
            break;
        }
        len++;
        *str++ = c;
    } while (c = inb(1));

    return s;
}