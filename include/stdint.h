#ifndef __STDINT_H__
#define __STDINT_H__

typedef signed char         int8_t;
typedef signed int          int16_t;
typedef signed long         int32_t;
typedef signed long long    int64_t;

typedef unsigned char       uint8_t;
typedef unsigned int        uint16_t;
typedef unsigned long       uint32_t;
typedef unsigned long long  uint64_t;

typedef signed int      intptr_t;
typedef unsigned int    uintptr_t;

#define INT8_MIN    (-128) 
#define INT16_MIN   (-32768)
#define INT32_MIN   (-2147483647 - 1)
#define INT64_MIN   (-9223372036854775807LL - 1)

#define INT8_MAX    127
#define INT16_MAX   32767
#define INT32_MAX   2147483647
#define INT64_MAX   9223372036854775807LL

#define UINT8_MAX   0xff                    /* 255U */
#define UINT16_MAX  0xffff                  /* 65535U */
#define UINT32_MAX  0xffffffff              /* 4294967295U */
#define UINT64_MAX  0xffffffffffffffffULL   /* 18446744073709551615ULL */

#define INTPTR_MIN  INT32_MIN
#define INTPTR_MAX  INT32_MAX
#define UINTPTR_MAX UINT32_MAX

#define PTRDIFF_MIN INT32_MIN
#define PTRDIFF_MAX INT32_MAX

#endif