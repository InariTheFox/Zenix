#include "cpu.h"
#include "stdarg.h"
#include "stdio.h"
#include "sys/kernel.h"

static char buf[256];

int printk(const char *fmt, ...)
{
    va_list args;
    int     i;
    char   *buf_end;

    di();

    va_start(args, fmt);
    i = vsprintf(buf + 3, fmt, args);
    buf_end = buf + 3 + i;
    va_end(args);

    ei();

    return i;
}