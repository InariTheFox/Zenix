#include "string.h"

void *memset(void *ptr, int value, size_t num) __sdcccall(0) __naked
{
    ptr, value, num;

    __asm

    pop hl
    pop de
    pop bc
    push hl

_loop:
    ld (hl), e
    inc hl
    ld (hl), d
    inc hl
    dec bc
    ld a, b
    or c
    jr nz, _loop

    pop hl
    ret
    
    __endasm;
}