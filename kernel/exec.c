#include "stdint.h"
#include "sys/errno.h"
#include "sys/kernel.h"
#include "sys/unistd.h"

/**
 * Execute a non-relocatable program.
 */
int execa(void *entry, const char **argv)
{
    entry;
    argv;

    return 0;
}