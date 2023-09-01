#include "cpu.h"
#include "dev.h"
#include "mm.h"
#include "stdint.h"
#include "stdlib.h"
#include "sys/errno.h"
#include "sys/fs.h"
#include "sys/kernel.h"
#include "sys/mm.h"
#include "sys/sched.h"
#include "sys/tty.h"
#include "sys/unistd.h"
#include "sys/utsname.h"
#include "sys/version.h"

uint32_t ramsize;
uint32_t procmem;

void init(void);

int device_init(void)
{
    printk("driver_init() not implemented\n");

    return ENOTIMPL;
}

void pagemap_init(void) { printk("pagemap_init() not implemented\n"); }

int tty_init(void)
{
    printk("tty_init() not implemented\n");

    return ENOTIMPL;
}

void main(void)
{
    printk(banner);

    ramsize = 65536;
    procmem = PROGTOP - PROGBASE;

    mm_init((uint16_t *)PROGBASE, procmem);
    tty_init();
    inode_init();
    pagemap_init();

    printk("%uKB total RAM ", ramsize / 1024);
    printk("%uKB available to processes ", procmem / 1024);
    printk("(%d processes max)\n", NR_TASKS);

    printk("Enabling interrupts...");
    ei();
    printk("OK.\n");

    device_init();

    sched_init();

    if (!fork())
    {
        const char *argv[] = {"init", NULL};
        execa(init, argv);
    }

    for (;;)
    {
        schedule();
    }
}