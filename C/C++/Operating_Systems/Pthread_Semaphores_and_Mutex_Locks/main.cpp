/**
 * @file main.cpp
 * @author Owen Man
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */

#include <iostream>
#include "buffer.h"
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <cstdlib>

using namespace std;

// Global Buffer Object
Buffer buffer;
sem_t sem;

// Prototypes
void *producer(void *param);
void *consumer(void *param);

/**
 * @brief Main function of the program
 * @param argc Number of command line arguments
 * @param argv Array of command line arguments
 *      argv[1] - sleep time (seconds)
 *      argv[2] - number of producer threads
 *      argv[3] - number of consumer threads
 * @return Integer indicating the exit status
 */
int main(int argc, char *argv[]) {
    /* Step 1: Get command line arguments argv[1],argv[2],argv[3] */
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " sleepTime producerThreads consumerThreads" << endl;
        return -1;
    }
    int sleepTime = atoi(argv[1]) * 1000000;  // Convert seconds to microseconds for usleep
    int producerThreads = atoi(argv[2]);
    int consumerThreads = atoi(argv[3]);

    /* Step 2: Initialize buffer and synchronization primitives */
    pthread_t producers[producerThreads];
    pthread_t consumers[consumerThreads];
    int ids[producerThreads];

    sem_init(&sem, 0, 1);

    /* Step 3: Create producer thread(s).
     * You should pass an unique int ID to each producer thread, starting from 1 to number of threads */
    for (int i = 0; i < producerThreads; i++) {
        ids[i] = i + 1; // unique producer ID
        if (pthread_create(&producers[i], NULL, producer, &ids[i])) {
            cerr << "Error creating producer thread " << ids[i] << endl;
        }
    }

    /* Step 4: Create consumer thread(s) */
    for (int i = 0; i < consumerThreads; i++) {
        if (pthread_create(&consumers[i], NULL, consumer, NULL)) {
            cerr << "Error creating consumer thread " << i + 1 << endl;
        }
    }

    /* Step 5: Main thread sleep */
    usleep(sleepTime);

    /* Step 6: Exit */
    cout << "Exiting program." << endl;
    return 0;
}

/**
 * @brief Producer thread function
 * @param param Pointer to the parameter passed to the thread
 * @return void pointer
 */
void *producer(void *param) {
    // Each producer insert its own ID into the buffer
    // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.
    int item = *((int *)param);
    while (true) {
        usleep(rand()%1000000); // sleep for a random period of time
        sem_wait(&sem); // synchronization
        if (buffer.insert_item(item)) {
            cout << "Producer " << item << ": Inserted item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Producer error condition" << endl;
        }
        sem_post(&sem); // synchronization
        return NULL;
    }
}

/**
 * @brief Consumer thread function
 * @param param Pointer to the parameter passed to the thread
 * @return void pointer
 */
void *consumer(void *param) {
    buffer_item item;
    while (true) {
        usleep(rand() % 1000000); // sleep for a random period of time
        sem_wait(&sem); // synchronization
        if (buffer.remove_item(&item)) {
            cout << "Consumer Removed item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Consumer error condition" << endl;
        }
        sem_post(&sem); // synchronization
        return NULL;
    }
}
