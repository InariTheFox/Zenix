#include "stddef.h"
#include "string.h"

size_t strlen(char *str) __naked
{
    str;

    // clang-format off
    __asm
    XOR A
    LD  B, A
    LD  C, A
    CPIR
    LD  HL, #-1
    SBC HL, BC
    EX  DE, HL
    RET
    __endasm;
    //clang-format on
}