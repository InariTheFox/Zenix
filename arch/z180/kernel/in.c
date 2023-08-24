#include "cpu.h"

uint8_t inb(uint8_t addr) __naked
{
    addr;
    
    // clang-format off
    __asm
    LD      C, A
    IN      A, (C)
    RET
    __endasm;
    // clang-format on
}