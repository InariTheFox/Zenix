#include "stddef.h"
#include "stdlib.h"
#include "string.h"
#include "cpu.h"
#include "sys/errno.h"
#include "sys/fs.h"
#include "sys/kernel.h"
#include "sys/sched.h"

struct inode_t *first_inode;
struct inode_t  inode_table[NR_INODE] = {
    {
        0,
    },
};
struct inode_operations_s root_ops = {

};

struct inode_t *inode_get_empty(void);
static int      find_entry(struct inode_t *, const char *, int,
                           struct dir_entry_t **);
void            free_inode(struct inode_t *);
static int      get_dir(const char *, struct inode_t **);
void            read_inode(struct inode_t *);
void            write_inode(struct inode_t *);

int last_allocated_inode = 0;

static int find_entry(struct inode_t *dir, const char *name, int namelen,
                      struct dir_entry_t **result)
{
    name;

    int entries;

    if (!namelen)
    {
        return NULL;
    }

    if (namelen > 64)
    {
        return NULL;
    }

    entries = dir->size / sizeof(struct dir_entry_t);
    *result = NULL;

    return NULL;
}

void free_inode(struct inode_t *inode)
{
    struct super_block_t *s;

    if (!inode)
    {
        return;
    }

    if (!inode->dev)
    {
        memset(inode, 0, sizeof(*inode));
    }

    if (inode->count > 1)
    {
        panic("Trying to free inode with count = %d\n", inode->count);
    }

    if (inode->nlinks)
    {
        panic("Trying to free inode with links\n");
    }

    if (!(s = get_super(inode->dev)))
    {
        panic("Trying to free inode on nonexistent device\n");
    }

    memset(inode, 0, sizeof(*inode));
}

static int get_dir(const char *filename, struct inode_t **result)
{
    filename;
    *result = NULL;

    if (!current->root || !current->root->count)
    {
        panic("No root inode!\n");
    }

    if (!current->pwd || !current->pwd->count)
    {
        panic("No cwd inode!\n");
    }

    return -ENOTIMPL;
}

int inode_dir_name(const char *filename, int *namelen, const char **name,
                   struct inode_t **result)
{
    const char *basename;
    int         error;

    error = get_dir(filename, result);
    if (error)
    {
        return error;
    }

    basename = filename;

    *namelen = filename - basename - 1;
    *name = basename;

    return 0;
}

void inode_init(void)
{
    printk("inode_init()\n");

    first_inode = NULL;
}

int inode_name(const char *filename, struct inode_t **result)
{
    const char *basename;
    int         namelen, error;

    error = inode_dir_name(filename, &namelen, &basename, result);
    if (error)
    {
        return error;
    }

    return 0;
}

struct inode_t *inode_get(int dev, int nr)
{
    struct inode_t *inode, *empty;

    if (!dev)
    {
        panic("inode_get with dev 0\n");
    }

    empty = inode_get_empty();
    inode = inode_table;

    while (inode < NR_INODE + inode_table)
    {
        if (inode->dev != dev || inode->ino != nr)
        {
            inode++;
            continue;
        }

        inode->count++;

        if (empty)
        {
            printk("pre-inode_put\n");
            inode_put(empty);
        }

        return inode;
    }

    if (!empty)
    {
        return NULL;
    }

    inode = empty;
    inode->dev = dev;
    inode->ino = nr;

    return inode;
}

struct inode_t *inode_get_empty(void)
{
    struct inode_t *inode;
    int             nr;

    printk("inode_get_empty()\n");

    while (1)
    {
        inode = NULL;
        nr = last_allocated_inode;

        do
        {
            if (!inode_table[nr].count)
            {
                inode = nr + inode_table;
            }

            nr++;

            if (nr >= NR_INODE)
            {
                nr = 0;
            }
        } while (nr != last_allocated_inode);

        if (!inode)
        {
            for (nr = 0; nr < NR_INODE; nr++)
            {
                printk("%x: %d\t", inode_table[nr].dev, inode_table[nr].ino);
            }

            panic("No free inodes in memory\n");
        }

        last_allocated_inode = nr;

        while (inode->dirty)
        {
        }

        if (!inode->count)
        {
            break;
        }
    }

    memset(inode, 0, sizeof(struct inode_t));
    inode->count = 1;

    halt();

    return inode;
}

void inode_put(struct inode_t *inode)
{
    printk("inode_put()\n");

    if (!inode)
    {
        return;
    }

    if (!inode->count)
    {
        panic("Trying to free free inode\n");
    }

    if (!inode->dev || inode->count > 1)
    {
        inode->count--;
        return;
    }

repeat:
    if (!inode->nlinks)
    {
        free_inode(inode);
        return;
    }

    if (inode->dirty)
    {
        write_inode(inode);
        goto repeat;
    }

    inode->count--;

    return;
}

void write_inode(struct inode_t *inode)
{
    struct super_block_t *s;

    s = get_super(inode->dev);

    inode->dirty = 0;
}