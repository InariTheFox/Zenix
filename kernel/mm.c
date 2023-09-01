#include "sys/mm.h"
#include "stddef.h"
#include "stdint.h"
#include "sys/kernel.h"

struct mm_block *first_free;
struct mm_block *mem_start;

void mm_init(uint16_t *base, uint16_t length)
{
    first_free = (struct mm_block *)base;
    first_free->size = length - sizeof(uint16_t);
    first_free->next = NULL;
    *mem_start = *first_free;

    printk("mm_init base: %x; length: %u bytes\n", base,
           length + sizeof(uint16_t));
}