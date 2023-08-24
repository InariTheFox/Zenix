#include "cpu.h"
#include "dev.h"
#include "mm.h"
#include "stdint.h"
#include "stdlib.h"
#include "sys/errno.h"
#include "sys/fs.h"
#include "sys/kernel.h"
#include "sys/mm.h"
#include "sys/process.h"
#include "sys/sched.h"
#include "sys/tty.h"
#include "sys/unistd.h"
#include "sys/utsname.h"
#include "sys/version.h"

struct mm_block  *first_free;
struct process_t *current_proc;
extern uint16_t   heap_start;
extern uint16_t   heap_end;
uint16_t          maxproc;
uint16_t          ramsize;
uint16_t          procmem;

void init(void);

int device_init(void)
{
    panic("drivers not implemented\n");

    return ENOTIMPL;
}

void pagemap_init(void) { panic("pagemap not implemented\n"); }

int tty_init(void)
{
    panic("tty not implemented\n");

    return ENOTIMPL;
}

void main(void)
{
    printk(banner);

    ramsize = (&heap_end - &heap_start) * sizeof(uint16_t);

    mm_init(&heap_start, ramsize);
    // tty_init();
    inode_init();
    // pagemap_init();

#ifdef PROC_SIZE
    maxproc = procmem / PROC_SIZE;
#else
    maxproc = PTABSIZE;
#endif
    procmem = 24576 / 16;

    printk("%dKB total RAM, %dKB available to processes (%d processes max)\n",
           ramsize, procmem, maxproc);

    printk("Enabling interrupts...");
    ei();
    printk("OK.\n");

    // device_init();

    proc_init();
    sched_init();

    if (!fork())
    {
        execa(init);
    }

    for (;;)
    {
    }
}