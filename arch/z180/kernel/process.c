#include "sys/process.h"
#include "context.h"
#include "stddef.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "sys/kernel.h"
#include "sys/sched.h"
#include "sys/types.h"

static struct process_t *ptab;
extern uint16_t         *stack_top;
extern uint16_t          heap_start;
pid_t                    next_pid;

struct process_t *proc_create(uint16_t stack_size)
{
    struct process_t *proc;
    pid_t             pid;

    proc = malloc(sizeof(struct process_t) + stack_size);

    if (!proc)
    {
        printk("could not create process\n");
        return NULL;
    }

    memset(proc, 0, sizeof(struct process_t));

    do
    {
        pid = next_pid++;

        if (pid < 0)
        {
            pid = 1;
        }
    } while (proc_find(pid));

    proc->pid = pid;
    proc->parent = current_proc;

    proc->stack = (uint16_t *)((uint8_t *)&proc[1] + stack_size);

    printk("proc_create: pid %d, parent pid: %d, base: %x, stack: %x\n", pid,
           proc->parent ? proc->parent->pid : -1, proc, proc->stack);

    return proc;
}

struct process_t *proc_find(pid_t pid)
{
    struct process_t *p = ptab;
    while (p)
    {
        if (p->pid == pid)
        {
            return p;
        }

        *p++;
    }

    return NULL;
}

void proc_init(void)
{
    struct process_t *idle;

    printk("proc_init()\n");

    ptab = NULL;
    current_proc = NULL;
    next_pid = 0;

    idle = proc_create(0);
    idle->parent = NULL;
    idle->stack = &stack_top;
    idle->state = TASK_RUNNING;

    current_proc = idle;
}