#include "stddef.h"
#include "sys/kernel.h"
#include "sys/sched.h"

void switch_to(struct process_t *next) __naked
{ 
    next;

    // clang-format off
    __asm
    ld a, #0x16
    add l
    ld l, a
    ld a, #0
    adc h
    ld h, a
    ld e, (hl)          ; Load exit_code into DE
    inc hl
    ld d, (hl)
    push de             ; Save exit_code
    ld a, #0x2D         
    add l
    ld l, a
    ld a, #0
    adc h
    ld h, a
    ld c, (hl)          ; Load SP into BC
    inc hl
    ld b, (hl)
    inc hl
    ld e, (hl)          ; Load PC into DE
    inc hl
    ld d, (hl)
    ld ix, #0           ; Load SP (BC) in to IX
    add ix, bc
    ex de, hl           ; Do the hokey-pokey
    pop de              ; Bring back our exit_code
    ld sp, ix           ; Set SP from IX
    jp (hl)
    __endasm;
    // clang-format on
}

uint16_t *context_get_sp(struct context_t *context)
{
    return (uint16_t *)context->sp;
}

void context_set_sp(struct context_t *context) __naked
{
    context;

    // clang-format off
    __asm
    ld c, 0(ix)
    ld b, 1(ix)
    ld e, 2(ix)
    ld d, 3(ix)
    ld (hl), c
    inc hl
    ld (hl), b
    inc hl
    ld (hl), e
    inc hl
    ld (hl), d
    ret
    __endasm;
    // clang-format on
}