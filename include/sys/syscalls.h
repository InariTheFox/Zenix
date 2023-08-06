#ifndef __SYS_SYSCALLS_H__
#define __SYS_SYSCALLS_H__

#include "stdint.h"

struct sysinfoblk
{
    uint8_t  banks;     /* Number of banks in memory */
    uint8_t  max_open;  /* Max open files */
    uint8_t  max_proc;  /* Max processes */
    uint16_t ticks;     /* Ticks in second*/
    uint16_t mem;       /* Memory in KB */
    uint16_t mem_used;  /* Used memory in KB */
    uint16_t swap;      /* Swap memory in KB */
    uint16_t swap_used; /* Used swap memory in KB */
};

#endif