#include "cpu.h"
#include "sys/fcntl.h"
#include "sys/fs.h"
#include "sys/kernel.h"
#include "sys/unistd.h"

extern int shell_main(int argc, char **argv);

void init(int argc, char **argv)
{
    argc, argv;
    uint16_t child, status;
    int      ret, stdin, stdout, stderr;

    printk("Init started. pid: %d\n", getpid());

    mount_root();

    chdir("/");

    stdin = open("/dev/tty0", O_RDWR);
    if (stdin != 0)
    {
        printk("Failed to open stdin with file descriptor 0\n");
    }

    stdout = dup(stdin);
    if (stdout != 1)
    {
        printk("Failed to open stdout with file descriptor 1\n");
    }

    stderr = dup(stdin);
    if (stderr != 2)
    {
        printk("Failed to open stderr with file descriptor 2\n");
    }

    while (1)
    {
        child = fork();
        if (!child)
        {
            printk("init: launching shell\n");

            const char *argv[] = {"sh", NULL};
            execa(shell_main, argv);
        }

        ret = waitpid(child, &status);
        printk("wait returned %d, status %x\n", ret, status);
    }
}