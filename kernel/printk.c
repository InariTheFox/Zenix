#include "cpu.h"
#include "stdarg.h"
#include "stdio.h"
#include "sys/kernel.h"

char buf[256];

int printk(const char *fmt, ...)
{
    va_list args;
    int     i;
    char   *buf_end;

    di();

    va_start(args, fmt);
    i = vsprintf(buf, fmt, args);
    buf_end = buf + i;
    va_end(args);

    puts(buf);

    ei();

    return i;
}