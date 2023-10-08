#include "string.h"

int strcmp(const char *str1, const char *str2)
{
    const char *s1 = str1;
    const char *s2 = str2;
    unsigned char c1, c2;

    do
    {
        c1 = (unsigned char) *s1++;
        c2 = (unsigned char) *s2++;

        if (c1 == '\0')
        {
            return c1 - c2;
        }
    } while (c1 == c2);

    return c1 - c2;    
}