# Driver-Conductor Model #

---

## Aim ##
Implement the driver-conductor model.

- There are one driver and two conductors on the bus which has two doors.
- Each conductor has management of one of the doors.
- The driver won't start the bus until all the doors are closed.
- The conductors will open the door when bus stops.

Each driver or conductor corresponding to a sperated thread, then finish the synchronization of the three threads by semaphore.

## Compile ##
Just execute `make` (make need to be installed) to make the program, and a file named "bus" will be generated.

The command `make clean` will clean all temporary files, including the executable program "bus".

## Usage ##
You must compile before run the program.

Enter `./bus` to execute the program.  
Then everything is to be done automatically, and each thread will tell you what it is doing by print something in terminal.

If you want to terminate the program, press enter directly.

## Advanced Usage ##
By default, it takes each conductor 3 seconds to close the door, and 5 to 7 seconds (randomly) for each stop, and 5 to 7 seconds for the bus to run from one station to another station.  
You could modify this by edit the source code.

## Others ##
The two conductors' name are Madoka and Homora, which comes from the animation *Puella Magi Madoka Magica*.

You could get the newest version of this program at:

- https://github.com/sqybi/OS-Homework/tree/master/Chapter2/p02

All the codes are published under:

- GNU General Public License v3
  http://www.gnu.org/licenses/gpl.html
