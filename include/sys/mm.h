#ifndef __SYS_MM_H__
#define __SYS_MM_H__

#include "stdint.h"

struct mm_block
{
    uint16_t         size;
    struct mm_block *next;
};

void mm_init(uint16_t *, uint16_t);
void pagemap_init(void);

#endif