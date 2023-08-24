#include "sys/errno.h"
#include "sys/unistd.h"
#include "sys/kernel.h"

int execa(void *ptr)
{
    printk("Executing code at %x\n", ptr);

    // clang-format off
    __asm
    JP (HL)
    __endasm;
    // clang-format on

    return 0;
}