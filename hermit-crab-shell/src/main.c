#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    while (true)
    {
        // Type prompt
        type_prompt();

        // read command and get parameters
        read_command(command, parameters);

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
    }
    return 0;
}
