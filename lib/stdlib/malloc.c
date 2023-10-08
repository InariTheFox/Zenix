#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "sys/kernel.h"
#include "sys/mm.h"

void free(void *ptr)
{
    struct mm_block *prev = first_free;

    first_free = (struct mm_block *)(ptr - sizeof(struct mm_block));

    memset(first_free, 0, first_free->size + sizeof(struct mm_block));

    first_free->next = prev;
}

void *malloc(size_t length)
{
    struct mm_block *cur;
    struct mm_block *prev = NULL;
    struct mm_block *next;

    if (length < sizeof(void *))
    {
        length = sizeof(struct mm_block);
    }

    printk("malloc: requesting %u bytes\n", length);

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
    printk("malloc: splitting block at %x (%u bytes)\n", cur, cur->size);

    next = (struct mm_block *)(cur + sizeof(struct mm_block) + length);
    next->next = cur->next;
    next->size = cur->size - length - sizeof(struct mm_block);

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

    printk("malloc: allocating %u bytes at %x\n", cur->size, cur);
    printk("malloc: %u bytes free remaining at %x\n", next->size, next);

    return (((uint8_t *)cur) + sizeof(uint16_t));
}