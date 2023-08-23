#ifndef __ARCH_Z180_FS_H__
#define __ARCH_Z180_FS_H__

#include "stdint.h"

struct inode_t
{
    uint16_t mode;
    uint16_t nlinks;
    uint8_t  uid;
    uint8_t  gid;
    uint32_t size;
    uint32_t atime;
    uint32_t mtime;
    uint32_t ctime;
};

struct super_block_t
{
    uint16_t ninodes;
    uint32_t max_size;
    uint16_t state;
};

struct dir_entry_t
{
    uint16_t inode;
    char     name[0];
};

#endif