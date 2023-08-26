#include "stdint.h"
#include "sys/kernel.h"
#include "sys/sched.h"
#include "sys/unistd.h"
#include "sys/utsname.h"

pid_t getpid(void)
{
    return current->pid;
}