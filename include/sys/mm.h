#ifndef __SYS_MM_H__
#define __SYS_MM_H__

#include "stdint.h"
#include "sys/types.h"

struct mm_block
{
    uint16_t         size;
    struct mm_block *next;
};

struct heap_t
{
    pid_t          owner;
    uint16_t       size;
    struct heap_t *next;
};

void mm_init(uint16_t *, uint16_t);
void pagemap_init(void);

#endif