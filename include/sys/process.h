#ifndef __SYS_PROCESS_H__
#define __SYS_PROCESS_H__

#include "context.h"
#include "stdint.h"
#include "sys/types.h"

struct process_t
{
    struct context_t  regs;
    struct process_t *parent;
    uint16_t         *stack;
    pid_t             pid;
    uint16_t          state;
    uint16_t          retval;
    struct inode_t   *cwd;
};

struct process_t *proc_create(uint16_t stack_size);
struct process_t *proc_find(pid_t pid);

uint16_t *context_get_sp(struct context_t *context);
void      context_set_sp(struct context_t *context, uint16_t *ptr);

void proc_init(void);

extern struct process_t *current_proc;

#endif