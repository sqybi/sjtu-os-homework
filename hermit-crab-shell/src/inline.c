#include "debug.h"

#include <stdio.h>
#include <stdlib.h>
#include "command.h"
#include "inline.h"

void cmd_cd(COMMAND_INFO info)
{
    char *dir;

    if (info.parameters_len == 1)
    {
        dir = "~";
    }
    else
    {
        dir = info.parameters[1];
    }

#ifdef DEBUG
    printf("[inline.c] dir = %s\n", dir);
#endif

    if (chdir(dir) != 0)
    {
        printf("[hcsh.cd] Directory not found.\n");
        // TODO(sqybi@126.com): I think this is the only reason to
        // result an error here. But a check is expected here to make
        // it better.
    }
}

void cmd_exit(COMMAND_INFO info)
{
    if (info.parameters_len == 1)
    {
#ifdef DEBUG
        printf("[inline.c] exiting without parameters.\n");
#endif
        exit(0);
    }
    else
    {
#ifdef DEBUG
        printf("[inline.c] exiting with parameters %s.\n", info.parameters[1]);
#endif
        exit(atoi(info.parameters[1]));
    }
}

void inline_cmd(COMMAND_INFO info)
{
    if (strcmp(info.command, "cd") == 0)
        cmd_cd(info);
    else if (strcmp(info.command, "exit") == 0)
        cmd_exit(info);
}
