#ifndef __SYS_SCHED_H__
#define __SYS_SCHED_H__

#define TASK_RUNNING         0
#define TASK_INTERRUPTABLE   1
#define TASK_UNINTERRUPTABLE 2
#define TASK_ZOMBIE          3
#define TASK_STOPPED         4
#define TASK_SWAPPING        5

void sched_init(void);

#endif