/*
 * Author: sqybi
 *
 *  This code aimed to simulate a driver and two conductors on the
 * same bus, and how they synchronize.
 *  Using threads and semaphores in the implementation.
 *  There are two doors on the bus, and each conductor will close one
 * of the door. When two doors are both closed, the driver starts the
 * car.
 *
 * Notification:
 *  When compiling, use
 *   gcc -pthread -o bus bus.o
 *  or the compile progress will not proceed correctly.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

// Consts
#define FALSE 0
#define TRUE 1
#define CLOSE 0
#define OPEN 1

// Variables
sem_t front_door, // the front door closed
      back_door, // the back door closed
      stop; // the car stops
pthread_t tdriver,
          tconductor1,
          tconductor2;

// Initialization
void initialize()
{
    // initialize semaphores
    sem_init(&front_door, 0, 0);
    sem_init(&back_door, 0, 0);
    sem_init(&stop, 0, 0);
    // initialize random seed
    srand(time(NULL));
}

// Destoying
void destoy()
{
    // destroy semaphores
    sem_destroy(&front_door);
    sem_destroy(&back_door);
    sem_destroy(&stop);
}

// The driver thread
//  Each of the conductors may send a message to notify the driver
// that doors are closed, but only one message will send at the same
// time.
void driver()
{
    while (TRUE)
    {
        // wait for the doors until closed
        sem_wait(&front_door);
        sem_wait(&back_door);
        // start the bus by random time
        printf("[Driver] The bus launches, please buy tickets.\n");
        sleep(5 + rand() % 3);
        // the bus stops
        printf("[Driver] The bus stops, please get down in turn.\n");
        sleep(3);
        sem_post(&stop);
        sem_post(&stop);
    }
}

// The first conductor thread
//  Conductor named Madoka, standing by front door.
void conductor1()
{
    while (TRUE)
    {
        // the passengers are getting on the bus
        printf("[Madoka] Hello passengers, please getting on the bus in turn.\n");
        sleep(5 + rand() % 3);
        // close the front door
        printf("[Madoka] The front door is closing...\n");
        sleep(3);
        sem_post(&front_door);
        // sell tickets and wait the car to stop
        printf("[Madoka] Tickets selling now!\n");
        sem_wait(&stop);
        // the car stops
        printf("[Madoka] The front door is opening...\n");
    }
}

// The second conductor thread
//  Conductor named Homora, standing by back door.
void conductor2()
{
    while (TRUE)
    {
        // the passengers are getting on the bus
        printf("[Homora] Hello passengers, please getting on the bus in turn.\n");
        sleep(5 + rand() % 3);
        // close the front door
        printf("[Homora] The back door is closing...\n");
        sleep(3);
        sem_post(&back_door);
        // sell tickets and wait the car to stop
        printf("[Homora] Tickets selling now!\n");
        sem_wait(&stop);
        // the car stops
        printf("[Homora] The back door is opening...\n");
    }
}

int main()
{
    initialize();

    // create three threads for driver and conductors
    printf("[Main] creating threads...\n");
    if (pthread_create(&tdriver, NULL, (void *)driver, NULL) != 0)
    {
        printf("[Main] Error when creating driver thread!\n");
        exit(1);
    }
    if (pthread_create(&tconductor1, NULL, (void *)conductor1, NULL) != 0)
    {
        printf("[Main] Error when creating conductor1 thread!\n");
        exit(2);
    }
    if (pthread_create(&tdriver, NULL, (void *)conductor2, NULL) != 0)
    {
        printf("[Main] Error when creating conductor2 thread!\n");
        exit(3);
    }
    printf("[Main] Threads successfully created!\n");
    printf("[Main] The car is currently stopping and story begins...\n");

    // Wait for exit until enter pressed
    printf("[Main] Press enter to exit the program.\n");
    getchar();
    destoy();
    printf("[Main] User stop the car >.<.\n");

    return 0;
}
