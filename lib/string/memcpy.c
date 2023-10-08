#include "stddef.h"
#include "string.h"
#include "stdint.h"

void *memcpy(void *destination, void *source, size_t length) __sdcccall(0) __naked
{
    destination, source, length;

    __asm
halt
    pop de
    pop hl
    pop bc
    push hl

    lddr

    pop hl
    ret

    __endasm;
}