#ifndef __SYS_TYPES_H__
#define __SYS_TYPES_H__

#include <stddef.h>

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long   size_t;
#endif

#ifndef _SSIZE_T
#define _SSIZE_T
typedef signed long     ssize_t;
#endif

typedef unsigned long   blkcnt_t;
typedef unsigned long   blksize_t;
typedef unsigned long   clock_t;
typedef unsigned int    dev_t;
typedef unsigned int    gid_t;
typedef unsigned long   ino_t;
typedef unsigned int    kdev_t;
typedef unsigned int    mode_t;
typedef long            off_t;
typedef int             pid_t;
typedef long            time_t;
typedef unsigned int    uid_t;

#endif