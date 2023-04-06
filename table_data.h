#ifndef TABLE_DATA_H
#define TABLE_DATA_H

#include <semaphore.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                           } while (0)
// Define the table size and the number of items to be produced
#define SIZE_DATA 2
#define MAX 6

// Define a structure for the Data table and its synchronization variables
struct Table {
    int items[SIZE_DATA];
    sem_t empty;
    sem_t full;
    pthread_mutex_t lock;
} table;

#endif

