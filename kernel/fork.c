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
    save_regs();

    int               nr;
    struct process_t *p;
    uint16_t         *src, *dst, *srclimit;

    printk("sp: %x, pc: %x\n", current->regs.sp, current->regs.pc);
    printk("af: %x, bc: %x\n", current->regs.af, current->regs.bc);
    printk("de: %x, hl: %x\n", current->regs.de, current->regs.hl);
    printk("ix: %x, iy: %x\n", current->regs.ix, current->regs.iy);

    if (!(p = malloc(sizeof(struct process_t) + STACK_SIZE)))
    {
        goto bad_fork;
    }

    nr = find_empty_proc();
    if (nr < 0)
    {
        goto bad_fork_cleanup;
    }

    src = (uint16_t *)current->kernel_stack;
    dst = (uint16_t *)((uint16_t)p + sizeof(struct process_t) + STACK_SIZE);

    srclimit = (uint16_t *)current->regs.sp;
    printk("fork: src %x, dst: %x, sp: %x\n", src, dst, srclimit);

    while (src > srclimit)
    {
        dst--;
        src--;
        *dst = *src;
    }

    *p = *current;
    p->state = TASK_UNINTERRUPTABLE;
    p->pid = last_pid;
    p->signal = 0;
    p->parent = current;
    p->prev = NULL;
    p->child = NULL;
    p->next = init_task;
    current->prev->next = p;
    current->prev = p;
    task[nr] = p;

    memcpy(&p->regs, &current->regs, sizeof(struct context_t));

    p->regs.sp = (uint16_t)dst;

    // TODO: pwd
    // TODO: root
    p->counter = current->counter >> 1;
    p->state = TASK_RUNNING;
    p->regs.de = 0;

    printk("sp: %x, pc: %x\n", p->regs.sp, p->regs.pc);
    printk("af: %x, bc: %x\n", p->regs.af, p->regs.bc);
    printk("de: %x, hl: %x\n", p->regs.de, p->regs.hl);
    printk("ix: %x, iy: %x\n", p->regs.ix, p->regs.iy);

    printk("fork: pid %d, counter %d, priority %d\n", p->pid, p->counter,
           p->priority);

    return p->pid;

bad_fork_cleanup:
    task[nr] = NULL;
bad_fork_free:
bad_fork:
    return -EAGAIN;
}