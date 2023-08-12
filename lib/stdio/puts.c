#include "stdio.h"
#include "string.h"
#include "cpu.h"

int puts(const char *str)
{
    int i, len;

    len = strlen(str);

    for (i = 0; i < len; i++)
    {
        outb(1, str[i]);
    }

    return i;
}