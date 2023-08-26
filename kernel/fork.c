#include "config.h"
#include "context.h"
#include "cpu.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "sys/errno.h"
#include "sys/kernel.h"
#include "sys/sched.h"
#include "sys/unistd.h"

#define MAX_TASKS_FOR_USER (NR_TASKS / 2)
#define MIN_TASKS_FOR_ROOT 4

pid_t last_pid = 0;

static int find_empty_proc(void)
{
    int free_task;
    int i, tasks_free;
    int this_user_tasks;

repeat:
    if ((++last_pid) & 0xff80)
    {
        last_pid = 1;
    }

    this_user_tasks = 0;
    tasks_free = 0;
    free_task = -EAGAIN;
    i = NR_TASKS;
    while (--i > 0)
    {
        if (!task[i])
        {
            free_task = i;
            tasks_free++;
            continue;
        }

        if (task[i]->uid == current->uid)
        {
            this_user_tasks++;
        }

        if (task[i]->pid == last_pid || task[i]->session == last_pid)
        {
            goto repeat;
        }
    }

    if (tasks_free <= MIN_TASKS_FOR_ROOT ||
        this_user_tasks > MAX_TASKS_FOR_USER)
    {
        if (current->uid)
        {
            return -EAGAIN;
        }
    }

    return free_task;
}

pid_t fork(void)
{
    int               nr;
    struct process_t *p;
    uint16_t         *src, *dst, *srclimit;

    if (!(p = malloc(sizeof(struct process_t) + STACK_SIZE)))
    {
        goto bad_fork;
    }

    nr = find_empty_proc();
    if (nr < 0)
    {
        goto bad_fork_cleanup;
    }

    src = &current->kernel_stack;
    dst = (uint16_t *)((uint16_t)p + sizeof(struct process_t) + STACK_SIZE);

    srclimit = context_get_sp(&current->regs);
    printk("fork: src %x, dst: %x, sp: %x\n", src, dst, srclimit);

    while (src > srclimit)
    {
        dst--;
        src--;
        *dst = *src;
    }

    context_set_sp(&p->regs, dst);

    *p = *current;
    p->state = TASK_UNINTERRUPTABLE;
    p->pid = last_pid;
    p->signal = 0;
    p->parent = current;
    p->prev = NULL;
    p->child = NULL;
    p->next = &init_task;
    init_task.prev->next = p;
    init_task.prev = p;
    task[nr] = p;

    // TODO: pwd
    // TODO: root
    p->counter = current->counter >> 1;
    p->state = TASK_RUNNING;

    printk("fork: pid %d, counter %d\n", p->pid, p->counter);

    return p->pid;

bad_fork_cleanup:
    task[nr] = NULL;
bad_fork_free:
bad_fork:
    return -EAGAIN;
}