#include "cpu.h"
#include "sys/kernel.h"
#include "sys/tty.h"
#include "sys/unistd.h"
#include "sys/utsname.h"

void main()
{
    tty_init();
    fstab_init();
    pagemap_init();

    struct utsname sysinfo;

    if (uname(&sysinfo) != 0)
    {
        panic("Cannot get uname.");
    }

    kprintf(
        "Zenix version %s\n"
        "Copyright (c) 2023 Brandon Dobbie\n\n",
        sysinfo.version);

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