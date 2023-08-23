#include "sys/kernel.h"
#include "sys/unistd.h"

void init(void)
{
    printk("Init started. pid: %d\n", getpid());
}