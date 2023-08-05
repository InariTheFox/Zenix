#ifndef __STDARG_H__
#define __STDARG_H__

#ifndef _VA_LIST
#define _VA_LIST
typedef char    *va_list;
#endif

#define __va_argsiz(t) (((sizeof(t) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))

#define va_start(a, n) ((a) = ((va_list) (&n) + __va_argsiz(n)))

#define va_end(a) ((void)0)

#define va_arg(a, t) (((a) = (a) + __va_argsiz(t)), *((t*)(void *)((a) - __va_argsiz(t))))

#endif