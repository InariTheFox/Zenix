#ifndef __ARCH_Z180_PAGE_H__
#define __ARCH_Z180_PAGE_H__

#define PAGE_SHIFT          12
#define PAGE_SIZE           (1 << PAGE_SHIFT)
#define PAGE_MASK           (~(PAGE_SIZE - 1))
#define PAGE_ALIGN(addr)    (((addr) + PAGE_SIZE - 1) & PAGE_MASK)
#define PAGE_OFFSET         0
#define MAP_NR(addr)        (((unsigned int)(addr)) >> PAGE_SHIFT)

#endif