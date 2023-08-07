#ifndef __SYS_TTY_DRIVER_H__
#define __SYS_TTY_DRIVER_H__

#include "fs.h"

struct tty_driver
{
    const char *name;  /* Name of device */
    char        num;   /* Number of devices */
    int         flags; /* Driver flags */

    int (*open)(struct tty_struct *tty, struct file *file);
    void (*close)(struct tty_struct *tty, struct file *file);
    int (*write)(struct tty_struct *tty, const unsigned char *buf, int count);
    void (*start)(struct tty_struct *tty);
    void (*stop)(struct tty_struct *tty);
    void (*hangup)(struct tty_struct *tty);
};

#endif