#ifndef __CONFIG_H__
#define __CONFIG_H__

#ifndef UTS_SYSNAME
#define UTS_SYSNAME     "Zenix"
#endif

#ifndef UTS_MACHINE
#define UTS_MACHINE     "unknown"
#endif

#define DEF_INITSEG     0x0000
#define DEF_SETUPSEG    0x0000
#define DEF_SYSSEG      0x1000
#define DEF_SYSSIZE     0x6F00

#endif