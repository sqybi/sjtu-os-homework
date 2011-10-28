#include "debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "command.h"
#include "inline.h"

void cmd_cd(COMMAND_INFO info)
{
    char *dir;

    if (info.parameters_len == 1)
    {
        dir = "/";
    }
    else
    {
        dir = info.parameters[1];
    }

#ifdef DEBUG
    fprintf(stderr, "[inline.c] dir = %s\n", dir);
#endif

    if (chdir(dir) != 0)
    {
        printf("[hcsh] Directory not found, or permission denied.\n");
        // TODO(sqybi@126.com): Check when is "not found", and when is
        // "permission denied". (or other cases?)
    }
}

void cmd_exit(COMMAND_INFO info)
{
    if (info.parameters_len == 1)
    {
#ifdef DEBUG
        fprintf(stderr, "[inline.c] exiting without parameters.\n");
#endif
        exit(0);
    }
    else
    {
#ifdef DEBUG
        fprintf(stderr, "[inline.c] exiting with parameters %s.\n", info.parameters[1]);
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
