#ifndef __SYS_FCNTL_H__
#define __SYS_FCNTL_H__

int fcntl(int, int, ...);

#define O_RDONLY    0
#define O_WRONLY    1
#define O_RDWR      2

#define O_APPEND        0x0008
#define O_RANDOM        0x0010
#define O_SEQUENTIAL    0x0020
#define O_TEMPORARY     0x0040

#define O_CREAT         0x0100
#define O_TRUNC         0x0200
#define O_EXCL          0x0400

#define O_TEXT          0x4000
#define O_BINARY        0x8000
#define O_RAW           O_BINARY

#ifndef _FMODE
#define _FMODE
typedef unsigned int    fmode;
#endif

int setmode(int, int);

#endif