# Reader-Writer Model #

---

## Aim ##
Implement the reader-writer model.

- There 4 readers and 4 writers, who are trying to access the database.
- When there is any other reader or writer in the database, the writer must
  wait for the access permission.
- The reader cannot get the access premission when some other writer is
  accessing the database, but able to have the permission when some other
  reader is in the database.
- Program must print the status of each reader and writer when catch a signal SIGINT.

Each reader or writer is corresponding to a sperated thread, then do the synchronization with other threads by semaphores.

## Compile ##
Just execute `make` (make need to be installed) to make the program, and a file named "rw" will be generated.

The command `make clean` will clean all temporary files, including the executable program "rw".

## Usage ##
You must compile before run the program.

Enter `./rw` to execute the program.

Then send a SIGINT signal to the process. In most Linux shells, `Ctrl-C` is used to send SIGINT.  
When catch a SIGINT signal, the program will print several lines of threads' status.

What's more, each reader and writer will take 1 to 5 seconds randomly when access the database, and sleep 1 to 5 seconds randomly when access finished.

If you want to terminate the program, press enter directly.

## Advanced Usage ##
You could modify the sleep time of the database accessing time by edit the source code.

## Others ##
The four readers are named *Ryuuji*, *Taiga*, *Minori* and *Ami*, which comes from animation *Tiger X Dragon*.  
The four writers are named *Makoto*, *Sekai*, *Kotonoha* and *Setsuna*, which comes from animation *School Days*.

You could get the newest version of this program at:

- https://github.com/sqybi/OS-Homework/tree/master/Chapter2/p03

All the codes are published under:

- GNU General Public License v3
  http://www.gnu.org/licenses/gpl.html
