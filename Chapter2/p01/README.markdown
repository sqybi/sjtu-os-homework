# Pipe File Monitoring #

---

## Aim ##
Use `fork()` to create multiple child processes, and monitor several pipe files at the same time (more than 3).

## Compile ##
Just execute `make` (make need to be installed) to make the whole project, and two files named "client" and "server" will be generated.

You could execute `make client` or `make server` to compile only one of the two programs.

The command `make clean` will clean all temporary files, including the executable programs "client" and "server".

## Usage ##
You must compile before run the two programs.

### Client ###
Use command `./client` to run the client program, and enter the number of pipes you'd like to monitor.  
Then, the program start to monitor these pipes in background.

Some pipe files may be created under current folder if not exist before. The pipe files' name looks like: pipe.1, pipe.2, ..., etc.

If you wanna quit the program, just press enter. The processes will be killed automatically.

### Server ###
Command `./server` is expected to run the server.

When server is running, you will be asked to enter the number of pipe which you want to send message to, and the content of the message. The pipe file's name is as described below.

If the number of pipe you input is -1, then the server will terminate.

## Advanced Usage ##
To change some parameters, like maximum number of pipes or maximum length of each message, you could edit "const.h" and recompile the whole project.

What's more, you could write to pipe file by `echo` or `cat` command manully, without running the server.

## Others ##
You could get the newest version of this program at:

-  https://github.com/sqybi/OS-Homework/tree/master/Chapter2/p01

All the codes are published under:

-  GNU General Public License v3
-  http://www.gnu.org/licenses/gpl.html
