#include "sys/kernel.h"
#include "stdarg.h"
#include "stdio.h"

void panic(const char *fmt, ...)
{
    static char buf[256];
    va_list args;

    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    va_end(args);

    printk("Kernel panic: %s\n", buf);

    for(;;);
}