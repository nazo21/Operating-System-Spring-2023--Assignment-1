#ifndef TABLE_DATA_H
#define TABLE_DATA_H

#include <semaphore.h>

// Define the table size and the number of items to be produced
#define SIZE_DATA 2
#define MAX 5

// Define a structure for the Data table and its synchronization variables
struct Table {
    int items[SIZE_DATA];
    sem_t empty;
    sem_t full;
    pthread_mutex_t lock;
} table;

#endif

