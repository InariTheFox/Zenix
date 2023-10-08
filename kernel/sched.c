#include "sys/sched.h"
#include "cpu.h"
#include "stdlib.h"
#include "string.h"
#include "sys/kernel.h"
#include "sys/unistd.h"

struct process_t *init_task;
struct process_t *current;
struct process_t *task[NR_TASKS];

#define idle_task (&init_task);

inline int goodness(struct process_t *p, struct process_t *prev)
{
    int weight;

    weight = p->counter;

    if (weight)
    {
        if (p == prev)
        {
            weight += 1;
        }
    }

    return weight;
}

void sched_init(void)
{
    printk("sched_init: base %x, tasks %d\n", task, NR_TASKS);

    for (int i = 1; i < NR_TASKS; i++)
    {
        task[i] = NULL;
    }

    init_task = malloc(sizeof(struct process_t));

    current = init_task;
    current->counter = 15;
    current->priority = 15;
    current->next = current;
    current->prev = current;
    current->parent = current;
    current->kernel_stack = (uint16_t)&init_kernel_stack_top;
    current->regs.sp = (uint16_t)&init_kernel_stack_top;

    printk("sched_init: stack %x\n", current->kernel_stack);
}

void schedule(void)
{
    int               c;
    struct process_t *p;
    struct process_t *prev, *next;

    di();

    prev = current;

    if (!prev->counter)
    {
        prev->counter = prev->priority;
    }

    switch (prev->state)
    {
    case TASK_INTERRUPTABLE:
        if (prev->signal & ~prev->blocked)
        {
            prev->state = TASK_RUNNING;
        }
        break;
    default:
    case TASK_RUNNING:
    }

    p = init_task->next;

    ei();

    c = -1000;
    next = *idle_task;

    while (p != init_task)
    {
        int weight = goodness(p, prev);
        if (weight > c)
        {
            c = weight, next = p;
        }

        p = p->next;
    }

    if (!c)
    {
        for (p = init_task; (p = p->next) != init_task;)
        {
            p->counter = (p->counter >> 1) + p->priority;
        }
    }

    if (prev != next)
    {
        printk("sched (%d): switching to pid %d, counter %d, priority %d\n",
               current->pid, next->pid, next->counter, next->priority);
        printk("sched: next base %x\n", next);

        current->prev = next;

        current = next;
        switch_to(current);
    }
}

pid_t waitpid(pid_t pid, int *status)
{
    printk("waitpid()\n");

    while (current)
    {
        if (current->parent == current && current->state == TASK_ZOMBIE)
        {
            printk("waitpid: found zombie child, pid %d\n", current->pid);

            if (pid != -1)
            {
                if (current->pid == pid)
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }

        printk("waitpid: current pid %d, next pid %d\n", current->pid, current->next->pid);

        current = current->next;
        schedule();

        printk("waitpid: returned\n");
    }

    if (current)
    {
        if (status)
        {
            *status = current->exit_code;
        }

        pid = current->pid;

        return pid;
    }
    else
    {
        printk("waitpid: schedule()\n");
        schedule();
    }

    return pid;
}