#ifndef __STDDEF_H__
#define __STDDEF_H__

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long size_t;
#endif

#ifndef offsetof
#define offsetof(st, m) ((size_t) & (((st *)0)->m))
#endif

#endif