#include "stdint.h"
#include "sys/errno.h"
#include "sys/kernel.h"
#include "sys/sched.h"
#include "sys/unistd.h"

/**
 * Execute a non-relocatable program.
 */
int execa(void *entry, const char **argv) __sdcccall(0)
{
    int argc = 0;
    const char **ptr;

    printk("execa: pid %d\n", getpid());

    ptr = argv;
    while (*ptr)
    {
        argc += 1;
        ptr++;
    }

    printk("execa: args %d\n", argc);

    current->start_code = (uint16_t)entry;
    current->arg_start = (uint16_t)argv;
    current->regs.pc = (uint16_t)entry;
    current->regs.hl = (uint16_t)argc;
    current->regs.de = (uint16_t)argv;

    switch_to(current);

    return 0;
}