#include "string.h"

void *memset(void *ptr, int value, size_t num)
{
    int i;
    int *d = ptr;

    for (i = 0; i < num; i++)
    {
        *d++ = value;
    }
}