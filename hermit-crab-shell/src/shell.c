#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include "function.h"

#define MAX_COMMAND_LENGTH 1024

char *command = NULL,
         *cwd = NULL;

void shell_initialize()
{

}

int main()
{
    //initialize
    //command = malloc(MAX_COMMAND_LENGTH);

    // initialize the shell
    shell_initialize();

    while (1)
    {
        //get current working directory
        if (cwd != NULL) free(cwd);
        cwd = get_current_dir_name();
        get_last_dir(&cwd);

        //read command
        if (command) free(command);
        command = readline(cwd);
/*
        //create child process
        int child_pid = fork();
        if (child_pid != 0) //here is parent process
        {
            int status;
            waitpid(child_pid, &status, 0);
        }
        else //here is child process
        {
            
        }
*/
    }
    return 0;
}
