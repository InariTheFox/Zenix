#include "fs.h"
#include "sys/fs.h"

static struct inode_t *first_inode;

void inode_init(void)
{
    first_inode = NULL;
}
