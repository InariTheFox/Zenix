#include "stddef.h"
#include "string.h"
#include "stdint.h"

void *memcpy(void *destination, void *source, size_t length)
{
    uint8_t       *dp = destination;
    const uint8_t *sp = source;

    while (length-- > 0)
    {
        *dp++ = *sp++;
    }

    return destination;
}