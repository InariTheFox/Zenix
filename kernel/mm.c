#include "sys/mm.h"
#include "stddef.h"
#include "stdint.h"
#include "sys/kernel.h"

extern struct mm_block *first_free;

void mm_init(uint16_t *base, uint16_t length)
{
    first_free = (struct mm_block *)base;
    first_free->size = length - sizeof(uint16_t);
    first_free->next = NULL;

    printk("mm_init base: %x; length: %d bytes\n", base,
           length + sizeof(uint16_t));
}