#include "sys/errno.h"
#include "sys/unistd.h"
#include "sys/kernel.h"

int execa(void *ptr)
{
    printk("Executing code at %h\n", ptr);

    __asm
    JP (HL)
    __endasm;

    return 0;
}