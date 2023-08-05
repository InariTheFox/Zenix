#ifndef __SYS_TTY_H__
#define __SYS_TTY_H__

#include "arch/z180/include/tty.h"
#include "tty_driver.h"
#include "fs.h"
#include "types.h"

struct tty_struct
{
    struct tty_driver   driver;
    struct termio       *termio;
    int                 session;
    kdev_t              device;
    unsigned int        flags;
    int                 count;
};

extern int rs_init(void);
extern int tty_init(void);

extern int rs_open(struct tty_struct *tty, struct file *file);

#endif