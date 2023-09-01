#ifndef __SYS_SCHED_H__
#define __SYS_SCHED_H__

#include "config.h"
#include "context.h"
#include "sys/types.h"

#define TASK_RUNNING         0
#define TASK_INTERRUPTABLE   1
#define TASK_UNINTERRUPTABLE 2
#define TASK_ZOMBIE          3
#define TASK_STOPPED         4
#define TASK_SWAPPING        5

void sched_init(void);

void schedule(void);

struct process_t
{
    volatile uint16_t state;       /* -1 unrunnable, 0 runnable, >0 stopped */
    uint16_t          counter;     /* */
    uint16_t          priority;    /* */
    uint16_t          signal;      /* */
    uint16_t          blocked;     /* bitmap of masked signals */
    uint16_t          flags;       /* per process flags */
    int16_t           errno;       /* */
    struct process_t *next, *prev; /* */
    struct process_t *parent, *child;                   /* */
    uint16_t          saved_kernel_stack, kernel_stack; /* kernel stack */
    uint16_t          start_code, end_code, start_data, end_data; /* */
    uint16_t          arg_start, arg_end, env_start, env_end;     /* */
    uint16_t          exit_code;                                  /* */
    pid_t             pid;                                        /* */
    uid_t             uid, euid;                                  /* */
    gid_t             gid, egid;                                  /* */
    uint16_t          session;                                    /* */
    uint32_t          utime, stime;                               /* */
    struct inode_t   *pwd;                                        /* */
    struct inode_t   *root;                                       /* */
    struct context_t  regs;                                       /* */
};

// clang-format off
/*#define INIT_TASK \
{ \
    0, 15, 15, 0, 0, 0, 0, \
    &init_task, &init_task, &init_task, NULL, \
    0, &init_kernel_stack, \
    0,0,0,0, \
    0,0,0,0, \
    0, \
    0, \
    0,0, \
    0,0, \
    0, \
    0,0, \
    NULL, \
    INIT_CONTEXT, \
}*/
// clang-format on

extern unsigned int  init_kernel_stack[2048];
extern unsigned int *init_kernel_stack_top;

extern struct process_t *init_task;
extern struct process_t *task[NR_TASKS];
extern struct process_t *current;

void switch_to(struct process_t *);

#endif