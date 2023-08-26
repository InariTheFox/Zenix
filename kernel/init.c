#include "sys/kernel.h"
#include "sys/unistd.h"
#include "cpu.h"

void init(void)
{
    printk("Init started. pid: %d\n", getpid());

    exit(-1);
}