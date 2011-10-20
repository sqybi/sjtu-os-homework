/*
 * Author: sqybi
 *
 *  This the messege sending server. It sends message to the client
 * by named pipes.
 *  Just enter the number of pipe, and the message, then program will
 * update the corresponding pipe. Then the client will check this
 * modification if it's running.
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
int i, p,
    fd; // file describer
char filename[MAX_FILENAME_LENGTH], // name of pipe
     message[MAX_MESSAGE_LENGTH]; // message to send

int main()
{
    while (TRUE)
    {
        // determine pipe to write
        printf("Which pipe is being written? Enter -1 to exit.\n");
        scanf("%d", &p);
        if (p == -1)
        {
            printf("Server terminated.\n");
            exit(0);
        }

        // get current pipe name
        sprintf(filename, "./pipe.%d", p);

        // enter message
        printf("Enter your message:\n");
        scanf("%s", message);

        // open pipe
        if ((fd = open(filename, O_WRONLY)) == -1) // failed
        {
            printf("Error when opening pipe!\n");
        }
        else // successful
        {
            // write message to pipe
            write(fd, message, MAX_MESSAGE_LENGTH);
            printf("Message successfully sent!\n");
        }
    }

    return 0;
}
