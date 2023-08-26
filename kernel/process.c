#include "sys/process.h"
#include "context.h"
#include "stddef.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "sys/kernel.h"
#include "sys/sched.h"
#include "sys/types.h"

struct process_t *ptab_head;
struct process_t *ptab_tail;
struct process_t *current_proc;
struct process_t *init_task;

extern uint16_t   heap_start;
pid_t             next_pid;
pid_t             last_pid;

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

    printk("proc_create: zeroing memory for process...\n");
    memset(proc, 0, sizeof(struct process_t));

    proc->pid = last_pid;
    proc->parent = current_proc;

    if (ptab_tail != NULL)
    {
        proc->prev = ptab_tail;
        ptab_tail->next = proc;
    }

    ptab_tail = proc;

    proc->stack = (uint16_t *)((uint8_t *)&proc[1] + stack_size);

    printk("proc_create: pid %d, parent pid %d, base %x, stack %x\n", pid,
           proc->parent ? proc->parent->pid : -1, proc, proc->stack);

    return proc;
}

struct process_t *proc_find(pid_t pid)
{
    struct process_t *p = ptab_head;

    while (p)
    {
        if (p->pid == pid)
        {
            return p;
        }

        p = p->next;
    }

    return NULL;
}