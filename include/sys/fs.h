#ifndef __SYS_FS_H__
#define __SYS_FS_H__

#include "stdint.h"
#include "sys/types.h"

#define NR_OPEN    16
#define NR_SUPER   8
#define NR_INODE   32
#define NR_FILE    64
#define BLOCK_SIZE 0

#define S_IFIFO 0x010
#define S_IFCHR 0x020
#define S_IFDIR 0x040
#define S_IFBLK 0x060
#define S_IFREG 0x100
#define S_ILINK 0x120
#define S_ISOCK 0x140

#define S_ISREG(m)  (((m) & S_IFREG) == S_IFREG)
#define S_ISDIR(m)  (((m) & S_IFDIR) == S_IFDIR)
#define S_ISLINK(m) (((m) & S_ILINK) == S_ILINK)
#define S_ISSOCK(m) (((m) & S_ISOCK) == S_ISOCK)

struct inode_t
{
    dev_t    dev;
    ino_t    ino;
    mode_t   mode;
    uint16_t nlinks;
    uid_t    uid;
    gid_t    gid;
    uint16_t count;
    uint16_t flags;
    uint8_t  locked;
    uint8_t  dirty;
    uint8_t  pipe;
    uint8_t  seek;
    uint32_t size;
    uint32_t atime;
    uint32_t mtime;
    uint32_t ctime;
};

struct super_block_t
{
    dev_t    dev;
    uint16_t ninodes;
    uint16_t blocksize;
    uint32_t max_size;
    uint16_t state;
};

struct dir_entry_t
{
    uint16_t inode;
    char     name[64];
};

struct file_t
{
    mode_t                    mode;
    dev_t                     dev;
    off_t                     pos;
    uint16_t                  flags;
    uint16_t                  count;
    struct file_t            *next, *prev;
    struct inode_t           *inode;
    struct file_operations_s *ops;
};

struct file_operations_s
{
    int (*read)(struct inode_t *, struct file_t *, char, int);
    int (*write)(struct inode_t *, struct file_t *, char *, int);
    int (*open)(struct inode_t *, struct file_t *);
};

struct inode_operations_s
{
    int (*create)(struct inode_t *, const char *, int, int, struct inode_t **);
    int (*link)(struct inode_t *, struct inode_t *, const char, int);
    int (*unlink)(struct inode_t *, const char *, int);
    int (*symlink)(struct inode_t *, const char *, int, const char *);
    int (*mkdir)(struct inode_t *, const char *, int, int);
    int (*rmdir)(struct inode_t *, const char *, int);
    int (*rename)(struct inode_t *, const char *, int, struct inode_t *,
                  const char *, int);
};

extern struct file_operations_s  chr_ops;
extern struct inode_operations_s inode_ops;

void inode_init(void);
void mount_root(void);

int             inode_dir_name(const char *, int *, const char **, struct inode_t **);
int             inode_name(const char *, struct inode_t **);
struct inode_t *inode_get(int, int);
void            inode_put(struct inode_t *);

extern struct file_t        file_table[NR_FILE];
extern struct super_block_t super_block[NR_SUPER];

inline struct super_block_t *get_super(int dev)
{
    struct super_block_t *s;

    for (s = 0 + super_block; s < NR_SUPER + super_block; s++)
    {
        if (s->dev == dev)
        {
            return s;
        }
    }

    return NULL;
}

#endif