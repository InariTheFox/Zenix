#ifndef __ARCH_Z180_CONFIG_H__
#define __ARCH_Z180_CONFIG_H__

#include "../../../include/kconfig.h"

#define NR_TASKS 16

#define MAX_MAPS  16 /* 8x 60KB banks, 1 is kernel */
#define MAX_SPLIT PROGTOP

#define CONFIG_BANKS 1 /* Banks as reported to user space */

#define PROGBASE     0x8000 /* Program base */
#define PROGLOAD     0x0100 /* Program vector */
#define PROGTOP      0xF000 /* Top of program */
#define KERNTOP      0x7FFF /* Kernel has lower 32KB */
#define STACK_SIZE   1024   /* Stack size in bytes */
#define DEFAULT_HEAP 1024   /* Default size of process heap */

#define Z180_IO_BASE 0xC0

#define NUM_DEV_TTY   2
#define BOOT_TTY      (512 + 1) /* UART0 as the console */
#define TTY_INIT_BAUD B115200

#define TTYDEV BOOT_TTY /* Device used by kernel for messages, panics, etc. */

#define ROOT_DEV 330

#endif