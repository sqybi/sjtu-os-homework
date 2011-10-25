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
#include "lexer.h"
#include "const.h"

// Variables
char *single_line,
     *prompt,
     line[STRING_MAX_LENGTH];

// Initialize all vairables of the shell, and other init operations
void shell_initialize(void)
{
    // clear the pointers
    single_line = NULL;
    prompt = NULL;
}


int main(int argc, char **argv)
{
    // initialize the shell
    shell_initialize();

    while (1)
    {
        // get last directory of current working directory
        if (prompt != NULL) free(prompt);
        prompt = get_prompt();

        // read command
        if (single_line) free(single_line);
        strcpy(line, "");
        single_line = readline(prompt);
        while (strlen(single_line) > 0 &&
                 single_line[strlen(single_line) - 1] == '\\')
        {
            strcat(line, single_line);
            if (single_line) free(single_line);
            single_line = readline(prompt);
            line[strlen(line) - 1] = '\0';
        }
        strcat(line, single_line);

        // get tokens

    }
    return 0;
}
