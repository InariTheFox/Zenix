#ifndef __SYS_FS_H__
#define __SYS_FS_H__

#include "sys/types.h"

struct file
{
    mode_t          mode;
    off_t           offset;
    unsigned int    flags;
    unsigned int    count;
    struct file     *next, *prev;
    int             owner;
};

#endif