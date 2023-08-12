#include "cpu.h"
#include "stdarg.h"
#include "stdio.h"
#include "sys/kernel.h"

void panic(const char *fmt, ...)
{
    char    buf[256];
    va_list args;

    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    va_end(args);

    printk("Kernel panic: %s\n", buf);

    for (;;)
    {
    }
}