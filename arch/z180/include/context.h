#ifndef __ARCH_Z180_CONTEXT_H__
#define __ARCH_Z180_CONTEXT_H__

#include "stdint.h"

struct context_t
{
    uint16_t sp;
    uint16_t pc;
    uint16_t af;
    uint16_t bc;
    uint16_t de;
    uint16_t hl;
    uint16_t ix;
    uint16_t iy;
};

uint16_t *context_get_sp(struct context_t *context);
void      context_set_sp(struct context_t *context);

// clang-format off
#define INIT_CONTEXT \
{ \
  &init_kernel_stack_top, 0, 0, 0, 0, 0, 0, 0\
}
// clang-format on

#endif

#define save_regs() __asm__("push iy\npush ix\npush hl\npush de\npush bc\npush af\nld c, 2(ix)\nld b, 3(ix)\npush bc\npush hl\nld hl, (_current)\nld a, #0x44\nadd l\nld l, a\nld a, #0\nadc h\nld h, a\nld b, #8\nregs_loop:\npop de\nld (hl), e\ninc hl\nld (hl), d\ninc hl\ndec b\nld a, #0\nor b\njr nz,regs_loop")