#include "sys/kernel.h"
#include "sys/sched.h"

void switch_to(struct process_t *next) { next; }

uint16_t *context_get_sp(struct context_t *context)
{
    return (uint16_t *)context->sp;
}

void context_set_sp(struct context_t *context, uint16_t *sp)
{
    context->sp = (uint16_t)sp;
}