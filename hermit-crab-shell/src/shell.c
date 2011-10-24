/*
 * Shell Main Process
 *
 *  Including some major functions for the whole shell.
 *  The main() function is here.
 */

// define _GNU_SOURCE to include the declare of get_current_dir_name()
#ifndef _GNU_SOURCE
#define  _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include "function.h"
#include "constant.h"

// Variables
char *line,
     *prompt;

// Initialize all vairables of the shell, and other init operations
void shell_initialize(void)
{
    // clear the pointers
    line = NULL;
    prompt = NULL;
}

// Run commands in cmd_list
void shell_run_commands(COMMAND_LIST cmd_list)
{

}

int main(int argc, char **argv)
{
    // variables
    COMMAND_LIST cmd_list;

    // initialize the shell
    shell_initialize();

    while (1)
    {
        // get last directory of current working directory
        if (prompt != NULL) free(prompt);
        prompt = get_prompt();

        // read command
        if (line) free(line);
        line = readline(prompt);

        // split input to COMMAND_LIST
        cmd_list = split_command(line);

        // run commands
        shell_run_commands(cmd_list);
    }
    return 0;
}
