#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/kernel.h"
#include "sys/unistd.h"

int shell_process(char *);

struct shell_s
{
    char    linebuf[256];
    char   *argv[16];
    int     argc;
    boolean end;
    int     exit_code;
};

int shell_main(int argc, char **argv)
{
    argc, argv;

    printk("Zenix integrated shell\n");

    int             ret = 0;
    struct shell_s *shell;

    shell = malloc(sizeof(struct shell_s));
    shell->end = false;

    printk("shell allocate\n");

    while (!shell->end)
    {
        getcwd(shell->linebuf, 256);
        printk("%s $ ", shell->linebuf);

        gets(shell->linebuf);

        if (shell_process(shell->linebuf))
        {
            printk("\n");
        }
        else
        {
            if (strcmp(shell->linebuf, "exit") == 0)
            {
                break;
            }

            printk("sh: %s: command not found\n", shell->linebuf);
        }
    }

    printk("shell exited\n");
    free(shell);

    return ret;
}

int shell_process(char *input)
{ 
    input;

    return 0; 
}