#include "config.h"
#include "sys/fs.h"
#include "sys/kernel.h"
#include "sys/sched.h"

struct super_block_t *mount(int);

struct super_block_t super_block[NR_SUPER];
struct file_t        file_table[NR_FILE];

void mount_root(void)
{
    int                   i, free;
    struct super_block_t *p;
    struct inode_t       *inode;

    for (i = 0; i < NR_FILE; i++)
    {
        file_table[i].count = 0;
    }

    for (p = &super_block[0]; p < &super_block[NR_SUPER]; p++)
    {
        p->dev = 0;
    }

    if (!(p = mount(ROOT_DEV)))
    {
        panic("Unable to mount root fs\n");
    }

    if (!(inode = inode_get(ROOT_DEV, 1)))
    {
        panic("Unable to read root inode\n");
    }

    inode->count += 3;
    current->pwd = inode;
    current->root = inode;
    free = 0;
    i = p->ninodes + 1;

    while (--i >= 0)
    {
        free++;
    }

    printk("%d/%d free inodes\n", free, p->ninodes);
}

struct super_block_t *mount(int dev)
{
    struct super_block_t *p;

    for (p = &super_block[0]; p < &super_block[NR_SUPER]; p++)
    {
        if (!(p->dev))
        {
            break;
        }
    }

    p->dev = (dev_t)-1;

    if (p >= &super_block[NR_SUPER])
    {
        return NULL;
    }

    p->dev = dev;

    return p;
}