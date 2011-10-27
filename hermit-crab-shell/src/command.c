#include "debug.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "inline.h"
#include "command.h"
#include "dir.h"

extern pid_t *pid_list,
             pid_list_len;
int *connect_pipe = NULL,
    in = 0,
    out = 1;

// initialize a COMMAND_INFO variable
void init_command_info(COMMAND_INFO *info)
{
    info->command = NULL;
    info->parameters = NULL;
    info->input_file = NULL;
    info->output_file = NULL;
    info->append_mode = 0;
    info->background_mode = 0;
    info->parameters_len = 0;
    info->output_to_pipe = 0;
}

// free all pointers in a COMMAND
// the pointers, e.g.command, input_file, etc., do not need to free()
// because they will be freed in free_token_list() in tokens.c
void free_command_info(COMMAND_INFO info)
{
    free(info.parameters);
}

// run a command
// informations have been writen in info
void run_command(COMMAND_INFO info)
{
    pid_t pid;
    int fd;
    char *temp;

#ifdef DEBUG
    printf("[command.c] hey, running command.\n");
#endif

    // deal with connect_pipes
    if (connect_pipe != NULL)
    {
        in = dup(0);
        close(0);
        dup(connect_pipe[0]);
        close(connect_pipe[0]);
        free(connect_pipe);
        connect_pipe = NULL;
    }
    if (info.output_to_pipe)
    {
        connect_pipe = calloc(sizeof(int), 2);
        out = dup(1);
        close(1);
        dup(connect_pipe[1]);
        close(connect_pipe[1]);
    }

    // input and output redirect
    if (info.input_file != NULL)
    {
        close(0);
        fd = open(info.input_file, O_RDONLY);
        dup(fd);
        close(fd);
    }
    if (info.output_file != NULL)
    {
        close(1);
        if (info.append_mode)
        {
            fd = open(info.output_file, O_WRONLY | O_APPEND);
            dup(fd);
            close(fd);
        }
        else
        {
            fd = open(info.output_file, O_WRONLY);
            dup(fd);
            close(fd);
        }
    }

    /* run commands below */

    // inline commands
    if (strcmp(info.command, "cd") == 0 ||
        strcmp(info.command, "exit") == 0)
    {
        if (!info.background_mode)
        {
            inline_cmd(info);
        }
        else
        {
            if ((pid = fork()) == 0)
            {
                inline_cmd(info);
            }
            else
            {
                printf("[hcsh] Process %d running in background.\n", pid);
            }
        }
    }
    // run a program
    else
    {
        // check the path of command
        temp = check_file_exist(info.command);
#ifdef DEBUG
        printf("[command.c] returned from check_file_exist()!\n");
#endif
        if (temp == NULL)
        {
            printf("[hcsh] Command \"%s\" not found!\n", info.command);
            return;
        }

        // fork
        if ((pid = fork()) == 0) // child process
        {
            // modify info.parameters
            // last item in info.parameters is NULL (what execvp() needed)
            info.parameters = realloc(info.parameters, sizeof(char *) * (info.parameters_len + 1));
            info.parameters[info.parameters_len] = NULL;
#ifdef DEBUG
            printf("[command.c] info.parameters[1] = %s, info.parameters = %d, with info.parameters_len = %d\n", info.parameters[1], info.parameters, info.parameters_len);
            printf("[command.c] info.command = %s\n", info.command);
#endif

            // RUN it!
            if (execv(temp, info.parameters) == -1)
            {
                // if exec error
                printf("[hcsh] Unknown error when executing exec().\n");
                exit(0);
            }
        }
        else // parent process
        {
            // add to wait list if not in background mode
            if (!info.background_mode)
            {
                ++pid_list_len;
                pid_list = realloc(pid_list, sizeof(pid_t) * pid_list_len);
                pid_list[pid_list_len - 1] = pid;
            }
            else
            {
                printf("[hcsh] Process %d running in background.\n", pid);
            }
            free(temp);
        }
    }

    /* run commands finished */

    // reset standard input and standard output
    if (in != 0)
    {
        close(0);
        in = dup(in);
    }
    if (out != 1)
    {
        close(1);
        out = dup(out);
    }
}

