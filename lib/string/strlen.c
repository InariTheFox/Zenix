#include "stddef.h"
#include "string.h"

size_t strlen(const char *str)
{
    int i = 0;

    while (*str != '\0')
    {
        str++;
    }

    return i;
}