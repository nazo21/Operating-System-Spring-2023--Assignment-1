#include <pthread.h>
#include <iostream>
#include "table_data.h"


using namespace std;

void *producer(void *arg) {
    int item = 1;
    for (int i = 0; i < MAX; i++) {
        // Wait for an empty slot on the table
        sem_wait(&table.empty_slots);

        // Acquire the lock to access the table
        pthread_mutex_lock(&table.lock);

        // Put the item on the table
        for (int j = 0; j < SIZE_DATA; j++) {
            if (table.items[j] == 0) {
                table.items[j] = item;
                cout << "Produced item " << item << endl;
                item++;
                break;
            }
        }

        // Release the lock and signal that a slot on the table is now full
        pthread_mutex_unlock(&table.lock);
        sem_post(&table.full_slots);
    }
    pthread_exit(NULL);
}

int main() {
    // Initialize the synchronization variables
    sem_init(&table.empty_slots, 0, SIZE_DATA);
    sem_init(&table.full_slots, 0, 0);
    pthread_mutex_init(&table.lock, NULL);

    // Create the producer and consumer threads
    pthread_t prod_thread;
    pthread_create(&prod_thread, NULL, producer, NULL);

    // Wait for the threads to finish
    pthread_join(prod_thread, NULL);

    // Clean up the synchronization variables
    sem_destroy(&table.empty_slots);
    sem_destroy(&table.full_slots);
    pthread_mutex_destroy(&table.lock);

    return 0;
}

