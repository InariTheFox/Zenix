#include "cpu.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"

char *itoa(int value, char *string, unsigned char radix)
{
    if (value < 0 && radix == 10)
    {
        *string++ = '-';
        value = -value;
    }

    char tmp[10];
    int  len = 0;

    if (value == 0)
    {
        *string++ = '0';
    }

    while (value > 0)
    {
        char digit = value % radix;

        if (digit < 10)
        {
            digit += '0';
        }
        else
        {
            digit += 'a' - 10;
        }

        tmp[len] = digit;
        len++;

        value = value / radix;
    }

    len -= 1;

    while (len >= 0)
    {
        *string++ = tmp[len];
        len--;
    }

    return string;
}