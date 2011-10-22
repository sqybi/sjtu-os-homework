/*
 * Author: sqybi
 *
 *  This the messege sending client. It receives message for server
 * by named pipes.
 *  The pipes are always named as: pipe.0, pipe.1, pipe.2, ... Under
 * current folder.
 *  This program will create multiple processes by fork(). Each child
 * process monitoring a pipe, and the main process will kill all the
 * processes when user press enter.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include "const.h"

/*
 * Variables
 */
int i,
    fd, // file describer
    pipe_num, // number of pipes to monitor
    pid, // child process id
    process_list[MAX_PIPE_NUM], // process list
    pipe_id;
char filename[MAX_FILENAME_LENGTH]; // name of pipe

/*
 * Initialize Function
 */
void initialize()
{
    umask(0); // clean umask
    memset(process_list, 0, sizeof(process_list));
}

/*
 * Kill Child Process
 *
 *  Kill first *num* child processes in process_list.
 */
void killChildProcess(int num)
{
    int pid; // process id to kill

    printf("[Main] Killing processes...\n");
    for (i = 0; i != num; ++i)
    {
        pid = process_list[i]; // get pid to kill
        if (kill(pid, 9) == 0) // successful
        {
            printf("[Main] Process %d (pipe.%d) successful killed.\n", pid, i);
        }
        else // failed
        {
            printf("[Main] Failed when killing process %d (pipe.%d).\n", pid, i);
        }
    }
    printf("[Main] Processes killing finished!\n");
}

/*
 * Parent Process
 *
 *  Fork a lot of processes to monitor different pipes.
 */
void parentProcess()
{
    // monitor a specified number of pipes
    printf("[Main] How many pipes to monitor?\n");
    scanf("%d", &pipe_num);

    // monitor each pipe
    for (i = 0; i != pipe_num; ++i)
    {
        // get current pipe name
        sprintf(filename, "./pipe.%d", i);

        // check if pipe doesn't exist
        if (access(filename, F_OK) == -1)
        {
            // create new pipe if not exist
            if (mkfifo(filename, 0666) == -1) //if failed
            {
                printf("[Main] Error when creating pipe, bye!\n");
                killChildProcess(i);
                exit(0);
            }
        }

        if ((pid = fork()) == 0) // this is a child process
        {
            pipe_id = i;
            return;
        }
        else //this is parent process
        {
            process_list[i] = pid; // record current child pid
        }
    }

    printf("[Main] All processes running, press enter to terminate.\n");
    getchar(); // clear the enter key pressed before
    getchar(); // wait until press enter
    killChildProcess(pipe_num);
    exit(0);
}

/*
 * Child Processes
 *
 *  Monitor a specified pipe, and print a message when text in pipe
 * changed.
 *  Reconize pipe by variable "filename" and "pipe_id".
 */
void childProcess()
{
    char message[MAX_MESSAGE_LENGTH], // message received currently
         pmessage[MAX_MESSAGE_LENGTH]; // message received previously

    printf("[P%d] Process running...\n", pipe_id);

    // open pipe
    if ((fd = open(filename, O_RDONLY)) == -1)
    {
        // if error, exit
        printf("[P%d] Open pipe error, process terminated.\n", pipe_id);
        exit(0);
    }

    // set init value for pmessage
    strcpy(pmessage, "");

    // read message from pipe
    while (TRUE)
    {
        // read message from pipe
		memset(message, 0, sizeof(message)); // clear message sent before
        read(fd, message, MAX_MESSAGE_LENGTH);
        if (strcmp(message, pmessage) != 0) // message changed!
        {
            // print message to screen
            printf("[P%d][M]:%s\n", pipe_id, message);
            // storage message
            strcpy(pmessage, message);
        }
    }
}

int main()
{
    initialize(); // initialize all variables
    parentProcess();
        // creates child processes, and kill them when exit
    childProcess();
        // Monitor change of a pipe
    return 0;
}
