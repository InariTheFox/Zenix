#include "sys/errno.h"
#include "sys/fs.h"
#include "sys/kernel.h"
#include "sys/sched.h"

int chdir(const char *filename)
{
    struct inode_t *inode;
    int             error;

    error = inode_name(filename, &inode);
    if (error)
    {
        return error;
    }

    if (!S_ISDIR(inode->mode))
    {
        return -ENOTDIR;
    }

    inode_put(current->pwd);
    current->pwd = inode;

    return 0;
}

int chroot(const char *filename)
{
    struct inode_t *inode;
    int             error;

    error = inode_name(filename, &inode);
    if (error)
    {
        return error;
    }

    if (!S_ISDIR(inode->mode))
    {
        return -ENOTDIR;
    }

    inode_put(current->root);
    current->root = inode;

    return 0;
}

int dup(int fd)
{
    fd;

    return -ENOTIMPL;
}

char *getcwd(char *buffer, size_t size)
{
    size;

    return buffer;
}

int open(const char *filename, int mode, ...)
{
    filename;
    mode;

    return -ENOTIMPL;
}