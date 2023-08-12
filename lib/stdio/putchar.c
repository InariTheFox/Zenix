#include "stdio.h"
#include "cpu.h"

int putchar(int character)
{
    outb(1, character);

    return 0;
}