#include "string.h"

char *strcpy(char *destination, const char *source)
{
    return memcpy(destination, source, strlen(source) + 1);
}