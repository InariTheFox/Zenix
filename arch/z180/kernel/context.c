#include "sys/process.h"

uint16_t *context_get_sp(struct context_t *context) { return (uint16_t *)context->sp; }

void context_set_sp(struct context_t *context, uint16_t *ptr)
{
    context->sp = (uint16_t)ptr;
}
