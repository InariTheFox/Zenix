#include "arch/z180/include/cpu.h"
#include "kernel.h"
#include "tty.h"

void main()
{
    tty_init();
    fstab_init();
    pagemap_init();

    kprintf(
        "Zenix version %s\n"
        "Copyright (c) 2023 Brandon Dobbie\n\n",
        sysinfo.uname);

#ifdef PROC_SIZE
    maxproc = procmem / PROC_SIZE;
#else
    maxproc = PTABSIZE;
#endif

    kprintf("%dKB total RAM, %dKB available to processes (%d processes max)\n", ramsize, procmem, maxproc);

    kprintf("Enabling interrupts...");
    ei();
    kprintf("OK.\n");

    device_init();
}