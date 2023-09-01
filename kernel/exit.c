#include "sys/errno.h"
#include "sys/kernel.h"
#include "sys/sched.h"
#include "sys/unistd.h"

void exit(int status)
{
    printk("exit: exit_code %d\n", status);
}