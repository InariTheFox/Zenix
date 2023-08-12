#include "cpu.h"
#include "stdint.h"

void outb(uint8_t addr, uint8_t value)
{
    addr;
    value;
    
    __asm
    LD      C, A
    OUT     (C), L
    __endasm;
}