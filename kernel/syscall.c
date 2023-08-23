#include "stdint.h"
#include "sys/kernel.h"
#include "sys/process.h"
#include "sys/unistd.h"
#include "sys/utsname.h"

pid_t getpid(void)
{
    return current_proc->pid;
}