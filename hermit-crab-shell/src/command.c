#include "debug.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "inline.h"
#include "command.h"
#include "dir.h"

extern pid_t *pid_list;
extern int pid_list_len;
static int *connect_pipe = NULL,
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
    info->wait_processes = 0;
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
void run_command(COMMAND_INFO *info)
{
    pid_t pid;
    char *full_name;
    void *temp;

    // deal with connect_pipes
    if (connect_pipe != NULL)
    {
#ifdef DEBUG
        fprintf(stderr, "[command.c] pipe 0\n");
#endif
        in = dup(0);
        close(0);
        dup(connect_pipe[0]);
        close(connect_pipe[0]);
        free(connect_pipe);
        connect_pipe = NULL;
    }
    if (info->output_to_pipe)
    {
#ifdef DEBUG
        fprintf(stderr, "[command.c] pipe 1\n");
#endif
        connect_pipe = calloc(sizeof(int), 2);
        pipe(connect_pipe);
        out = dup(1);
        close(1);
        dup(connect_pipe[1]);
        close(connect_pipe[1]);
    }

    // input and output redirect
    if (info->input_file != NULL)
    {
#ifdef DEBUG
        fprintf(stderr, "[command.c] input\n");
#endif
        in = dup(0);
        close(0);
        open(info->input_file, O_RDONLY);
    }
    if (info->output_file != NULL)
    {
#ifdef DEBUG
        fprintf(stderr, "[command.c] output\n");
#endif
        out = dup(1);
        close(1);
        if (info->append_mode)
        {
            open(info->output_file, O_WRONLY | O_APPEND);
        }
        else
        {
            open(info->output_file, O_WRONLY);
        }
    }

    /* run commands below */

    // inline commands
    if (strcmp(info->command, "cd") == 0 ||
        strcmp(info->command, "exit") == 0)
    {
        if (!info->background_mode)
        {
            inline_cmd(*info);
        }
        else
        {
            if ((pid = fork()) == 0)
            {
                inline_cmd(*info);
                exit(0);
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
        full_name = check_file_exist(info->command);
        if (full_name == NULL)
        {
            if (access(info->command, 0) == 0)
            {
                full_name = calloc(sizeof(char *), strlen(info->command) + 1);
                strcpy(full_name, info->command);
            }
            else
            {
                printf("[hcsh] Command \"%s\" not found!\n", info->command);
                return;
            }
        }

        // fork
        if ((pid = fork()) == 0) // child process
        {
            // reset SIGINT
            if (!info->background_mode)
                signal(SIGINT, SIG_DFL);

            // modify info->parameters
            // last item in info->parameters is NULL (what execvp() needed)
            temp = realloc(info->parameters, sizeof(char *) * (info->parameters_len + 1));
            if (temp != NULL)
                info->parameters = (char **) temp;
            info->parameters[info->parameters_len] = NULL;

            // RUN it!
            if (execv(full_name, info->parameters) == -1)
            {
                // if exec error
                printf("[hcsh] Unknown error when executing exec().\n");
                exit(0);
            }
        }
        else // parent process
        {
            // add to wait list if not in background mode
            if (!info->background_mode)
            {
                ++pid_list_len;
                temp = realloc(pid_list, sizeof(pid_t) * pid_list_len);
                if (temp != NULL)
                    pid_list = (pid_t *) temp;
                pid_list[pid_list_len - 1] = pid;
            }
            else
            {
                printf("[hcsh] Process %d running in background.\n", pid);
            }
        }

        // free
        free(full_name);
    }

    /* run commands finished */

    // reset standard input and standard output
    if (in != 0)
    {
        close(0);
        dup(in);
        close(in);
        in = 0;
    }
    if (out != 1)
    {
        close(1);
        dup(out);
        close(out);
        out = 1;
    }
}

