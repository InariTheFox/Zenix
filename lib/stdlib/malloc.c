#include "stdint.h"
#include "stdlib.h"
#include "sys/mm.h"
#include "sys/kernel.h"

extern struct mm_block *first_free;

void *malloc(size_t length)
{
    struct mm_block *cur;
    struct mm_block *prev = NULL;
    struct mm_block *next;

    if (length < sizeof(void *))
    {
        length = sizeof(struct mm_block);
    }

    printk("malloc: requesting %d bytes\n", length);

    length = (length + 1) & -2;

    cur = first_free;

    while (cur)
    {
        if (cur->size == length)
        {
            next = cur->next;
            goto alloc;
        }

        if (cur->size > length)
        {
            goto split;
        }

        prev = cur;
        cur = cur->next;
    }

    return NULL;

split:
    printk("malloc: splitting block at %x (%d bytes)\n", cur, cur->size);

    next = (struct mm_block *)(cur + sizeof(uint16_t) + length);
    next->next = cur->next;
    next->size = cur->size - length - sizeof(uint16_t);

alloc:
    if (cur == first_free)
    {
        first_free = next;
    }
    else
    {
        prev->next = next;
    }

    cur->size = length;

    printk("malloc: allocating %d bytes at %x\n", cur->size, cur);
    printk("malloc: %d bytes free remaining at %x\n", next->size, next);

    return (((uint8_t *)cur) + sizeof(uint16_t));
}