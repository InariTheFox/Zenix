#ifndef __SYS_KERNEL_H__
#define __SYS_KERNEL_H__

#include "stdint.h"

#ifndef NULL
#define NULL (void *)0
#endif

#define min(a, b)       ((a) < (b) ? (a) : (b))
#define max(a, b)       ((a) > (b) ? (a) : (b))
#define aligndown(v, a) (uint8_t *)((intptr_t)(v) & ~((a)-1))
#define alignup(v, a)   (uint8_t *)((intptr_t)((v) + (a)-1) & ~((a)-1))

#ifndef ALIGNUP
#define ALIGNUP(v) (v)
#endif

#ifndef ALIGNDOWN
#define ALIGNDOWN(v) (v)
#endif

#ifndef UNALIGNED
#define UNALIGNED(x) 0
#endif

#define OS_BANK   0
#define NO_DEVICE (0xFFFFU)
#define NO_FILE   (0xFF)

#ifndef PTABSIZE
#define PTABSIZE 15
#endif

extern uint32_t ramsize;
extern uint32_t procmem;

struct p_tab
{
    uint8_t status;
    uint8_t flags;
#define PFL_CHECKSIG 1;
#define PFL_ALARM    2;
#define PFL_BATCH    4;
#define PFL_GRAPHICS 8;
    uint8_t  tty;
    uint16_t pid;
    uint16_t uid;
    uint16_t alarm;    /* Milliseconds until alarm */
    uint16_t exit_val; /* Exit value */
    void    *wait;
    uint16_t page;
    uint16_t priority;
};

void main(void);
int  printk(const char *, ...);
void panic(const char *, ...);

#endif