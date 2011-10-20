/*
 * Author: sqybi
 *
 *  This program implements a Reader-Writer Model.
 *  You could use Ctrl-C under most linux shell to send SIGINT to
 * this program, and it will tell you the status of each thread.
 *
 *  TODO(sqybi): Combine reader and writer together. Language with
 *               class (e.g. Java) may be needed.
 */

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

// Consts
#define FALSE 0
#define TRUE 1
#define MAX_READER_NUM 4
#define MAX_WRITER_NUM 4
#define MAX_STATUS_NUM 3
#define OUT 0
#define WAITING 1
#define IN 2
const char* reader_name[MAX_READER_NUM]
                        = {"Ryuuji", "Taiga", "Minori", "Ami"};
                           // name from "Tiger X Dragon"
const char* writer_name[MAX_WRITER_NUM]
                        = {"Makoto", "Sekai", "Kotonoha", "Setsuna"};
                           // name from "School Days"
const char* status[MAX_STATUS_NUM]
                   = {"doing nothing", "waiting for its turn", "in the database"};
                      // different status

// Variables
sem_t mutex, // lock for reader_count
      database; // control the visit of the database
unsigned int reader_count, // current count of readers in database
             reader_status[MAX_READER_NUM], // status of each reader
             writer_status[MAX_WRITER_NUM]; // status of each writer
pthread_t reader_tid[MAX_READER_NUM], // tid of each reader thread
          writer_tid[MAX_WRITER_NUM]; // tid of each writer thread

// when catch SIGINT
void sig(int s)
{
    int i;

    printf("\n===== Status of readers and writers =====\n");

    // print status of each reader
    for (i = 0; i != MAX_READER_NUM; ++i)
    {
        printf("Reader #%d - %s - is now %s.\n", i + 1, reader_name[i], status[reader_status[i]]);
    }

    // print status of each writer
    for (i = 0; i != MAX_WRITER_NUM; ++i)
    {
        printf("Writer #%d - %s - is now %s.\n", i + 1, writer_name[i], status[writer_status[i]]);
    }

    printf("===== END =====\n");
}

// Check number for a reader
// return the number
int check_reader()
{
    // variables
    int i;
    pthread_t tid;

    // check tid
    tid = pthread_self();
    for (i = 0; i != MAX_READER_NUM; ++i)
    {
        if (tid == reader_tid[i])
            break;
    }
    if (i == MAX_READER_NUM) // This SHOULD NOT happen!
    {
        printf("Unknown tid %d, WTF!\n", tid);
        exit(3);
    }

    return i;
}

// Check number for a writer
// return the number
int check_writer()
{
    // variables
    int i;
    pthread_t tid;

    // check tid
    tid = pthread_self();
    for (i = 0; i != MAX_WRITER_NUM; ++i)
    {
        if (tid == writer_tid[i])
            break;
    }
    if (i == MAX_WRITER_NUM) // This SHOULD NOT happen!
    {
        printf("Unknown tid %d, WTF!\n", tid);
        exit(3);
    }

    return i;
}

// Reader Thread
void reader()
{
    // variables
    int i, id;
    char *real_name;
    sigset_t set;

    // ignore SIGINT
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    // get reader number
    id = check_reader();

    while (TRUE)
    {
        sleep(1 + rand() % 5);

        // wait to read
        reader_status[id] = WAITING;
        sem_wait(&mutex); // lock reader_count
        reader_count++; // new reader
        if (reader_count == 1) // if I'm the first reader
            sem_wait(&database); // wait until all writers are out
        sem_post(&mutex); // unlock reader_count

        // read
        reader_status[id] = IN;
        sleep(1 + rand() % 5); // reading...

        // finish reading
        sem_wait(&mutex); // lock reader_count
        reader_count--; // leave the database
        if (reader_count == 0) // If I'm the last reader
            sem_post(&database); // The writers can be in now
        sem_post(&mutex); // unlock reader_count
        reader_status[id] = OUT;
    }
}

// Writer Thread
void writer()
{
    // variables
    int i, id;
    char *real_name;
    sigset_t set;

    // ignore SIGINT
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    // get reader number
    id = check_writer();

    while (TRUE)
    {
        sleep(1 + rand() % 5);

        // wait to write
        writer_status[id] = WAITING;
        sem_wait(&database); // until all readers and writers are out

        // write
        writer_status[id] = IN;
        sleep(1 + rand() % 5); // writing...

        // finish reading
        sem_post(&database); // others can use the database now
        writer_status[id] = OUT;
    }
}

// Initialization
void initialize()
{
    // catch SIGINT
    signal(SIGINT, sig);
    // initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&database, 0, 1);
    // no readers when program begin
    reader_count = 0;
    // initialize rand seed
    srand(time(NULL));
}

int main()
{
    // Variables
    int i;

    // Initialization
    initialize();

    // Create Reader Threads
    printf("[Main] Creating readers...");
    for (i = 0; i != MAX_READER_NUM; ++i)
    {
        if (pthread_create(&reader_tid[i], NULL, (void *) reader, NULL) != 0)
        {
            printf("[Main] Error when creating reader thread #%d!\n", i);
            exit(1);
        }
        else
        {
            printf("%d...", reader_tid[i]);
        }
    }
    printf("success!\n");


    // Create Writer Threads
    printf("[Main] Creating writers...");
    for (i = 0; i != MAX_WRITER_NUM; ++i)
    {
        if (pthread_create(&writer_tid[i], NULL, (void *) writer, NULL) != 0)
        {
            printf("[Main] Error when creating writer thread #%d!\n", i);
            exit(2);
        }
        else
        {
            printf("%d...", writer_tid[i]);
        }
    }
    printf("success!\n");

    // press enter to exit
    printf("[Main] Press enter to terminate.\n");
    getchar();
    printf("[Main] The database has been closed. Bye bye!\n");

    return 0;
}
