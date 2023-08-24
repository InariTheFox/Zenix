#include "stdint.h"
#include "string.h"
#include "sys/errno.h"
#include "sys/kernel.h"
#include "sys/process.h"
#include "sys/sched.h"
#include "sys/unistd.h"

pid_t fork(void)
{
    printk("Forking...\n");

    struct process_t *child;
    uint16_t *src, *dst, *sp;

    child = proc_create(STACKSIZE);

    if (!child)
    {
        return -ENOMEM;
    }

    child->state = TASK_RUNNING;

    memcpy(&child->regs, &current_proc->regs, sizeof(struct context_t));

    src = current_proc->stack;
    dst = child->stack;

    // clang-format off
    __asm
    exx                     ; Backup registers

    ld hl, #0
    add hl, sp              ; Load SP in to HL
    ex de, hl               ; Backup SP as we need it later
    ld bc, #_current_proc   ; Load in to BC pointer to the current process struct
    ld l, c                 ; Load BC in to HL
    ld h, b
    ld c, (hl)              ; Load in to BC the pointers memory location
    inc hl
    ld b, (hl)
    ld l, c                 ; Load in to HL the pointer memory location
    ld h, b
    ld (hl), e              ; Set SP in the struct
    inc hl
    ld (hl), d

    exx                     ; Restore registers
    __endasm;
    // clang-format on

    sp = context_get_sp(&current_proc->regs);

    printk("src stack: %x, dest stack: %x, current SP: %x (%x)\n", src, dst, sp, current_proc);

    while (src > sp)
    {
        dst--;
        src--;
        *dst = *src;
    }
    
    context_set_sp(&child->regs, dst);

    printk("src sp: %x, dest sp: %x\n", src, dst);

    child->cwd = current_proc->cwd;

    return child->pid;
}