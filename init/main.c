#include "cpu.h"
#include "dev.h"
#include "stdint.h"
#include "sys/errno.h"
#include "sys/kernel.h"
#include "sys/mm.h"
#include "sys/sched.h"
#include "sys/tty.h"
#include "sys/unistd.h"
#include "sys/utsname.h"

uint16_t maxproc;
uint16_t ramsize;
uint16_t procmem;

int device_init(void)
{
    panic("drivers not implemented\n");

    return ENOTIMPL;
}

void fstab_init(void)
{
    panic("fstab not implemented\n");
}

void pagemap_init(void)
{
    panic("pagemap not implemented\n");
}

int tty_init(void)
{
    panic("tty not implemented\n");

    return ENOTIMPL;
}

void main(void)
{
    tty_init();
    fstab_init();
    pagemap_init();

    struct utsname sysinfo;

    if (uname(&sysinfo) != 0)
    {
        panic("Cannot get uname.");
    }

    printk("Zenix version %s\n"
           "Copyright (c) 2023 Brandon Dobbie\n\n",
           sysinfo.version);

#ifdef PROC_SIZE
    maxproc = procmem / PROC_SIZE;
#else
    maxproc = PTABSIZE;
#endif

    printk("%dKB total RAM, %dKB available to processes (%d processes max)\n",
           ramsize, procmem, maxproc);

    printk("Enabling interrupts...");
    ei();
    printk("OK.\n");

    device_init();

    sched_init();
}