#ifndef __ARCH_Z180_CONTEXT_H__
#define __ARCH_Z180_CONTEXT_H__

#include "stdint.h"

struct context_t
{
    uint16_t sp;
    uint16_t pc;
    uint16_t iy;
    uint16_t ix;
    uint16_t hl;
    uint16_t de;
    uint16_t bc;
    uint16_t af;
};

#endif