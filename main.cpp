#include <iostream>
#include <pthread.h>
#include <semaphore.h>

using namespace std;
/*
   This is the program where if run it will work intended
   However where I went wrong is I should've implemented a while(MAX){Produce two at a time in table}

*/
// Define the table size and the number of items to be produced
#define SIZE 2
#define ITEMS 6

// Define a structure for the table and its associated synchronization variables
struct Table {
    int items[SIZE];
    sem_t empty;
    sem_t full;
    pthread_mutex_t lock;
} table;

// Define the producer thread function
void *producer(void *nun) {
    int item = 1;
    for (int i = 0; i < ITEMS; i++) {
        // Wait for an empty slot on the table
        sem_wait(&table.empty);

        // Acquire the lock to access the table
        pthread_mutex_lock(&table.lock);

        // Put the item on the table
        for (int j = 0; j < SIZE; j++) {
            if (table.items[j] == 0) {
                table.items[j] = item;
                cout << "Produced item " << item << endl;
                item++;
                break;
            }
        }

        // Release the lock and signal that a slot on the table is now full
        pthread_mutex_unlock(&table.lock);
        sem_post(&table.full);
    }
    pthread_exit(NULL);
}

// Define the consumer thread function
void *consumer(void *cnun) {
    for (int i = 0; i < ITEMS; i++) {
        // Wait for a full slot on the table
        sem_wait(&table.full);

        // Acquire the lock to access the table
        pthread_mutex_lock(&table.lock);

        // Take an item off the table
        for (int j = 0; j < SIZE; j++) {
            if (table.items[j] != 0) {
                int item = table.items[j];
                table.items[j] = 0;
                cout << "Consumed item " << item << endl;
                break;
            }
        }

        // Release the lock and signal that a slot on the table is now empty
        pthread_mutex_unlock(&table.lock);
        sem_post(&table.empty);
    }
    pthread_exit(NULL);
}

int main() {
    // Initialize the synchronization variables
    sem_init(&table.empty, 0, SIZE);
    sem_init(&table.full, 0, 0);
    pthread_mutex_init(&table.lock, NULL);

    // Create the producer and consumer threads
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for the threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Destroy the synchronization variables
    sem_destroy(&table.empty);
    sem_destroy(&table.full);
    pthread_mutex_destroy(&table.lock);

    return 0;
}

