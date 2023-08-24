#include "sys/sched.h"
#include "sys/kernel.h"
#include "sys/process.h"

void sched_init(void) { printk("sched_init()\n"); }

void switch_context(process_t *next)
{
    // We should have saved the stack pointer for the current task when a fork()
    // is called. Fork() should be what's happening to spawn any process,
    // including when execa/execv/execve is called.

    // clang-format off
    __asm

    push af                 ; Push registers to stack in reverse order of context_t
    push bc
    push de
    push hl
    push ix
    push iy

    ld de, #_current_proc   ; Load in to BE pointer to the current process struct
    inc de                  ; Increment DE by 4 as context_t first field is SP
    inc de
    inc de
    inc de

    ld hl, #4               ; Load SP into HL and add 4 to offset
    add hl, sp

    ld bc, #12              ; Set the number of bytes to read

    ldir                    ; Load (HL) into (DE) and decrement BC until 0

    __endasm;
    // clang-format on
}