#include "sys/sched.h"
#include "cpu.h"
#include "sys/kernel.h"

unsigned int init_kernel_stack[STACK_SIZE] = {
    0,
};
struct process_t  init_task = INIT_TASK;
struct process_t *current = &init_task;
struct process_t *task[NR_TASKS] = {
    &init_task,
};

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
    int i;

    printk("sched_init()\n");

    for (i = 1; i < NR_TASKS; i++)
    {
        task[i] = NULL;
    }
}

void schedule(void)
{
    printk("schedule()\n");
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

    p = init_task.next;

    ei();

#define idle_task (&init_task);

    c = -1000;
    next = idle_task;

    while (p != &init_task)
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
        for (p = &init_task; (p = p->next) != &init_task;)
        {
            p->counter = (p->counter >> 1) + p->priority;
        }
    }

    if (prev != next)
    {
        printk("sched: switching to pid %d, counter %d, priority %d\n",
               next->pid, next->counter, next->priority);

        switch_to(next);
    }
}