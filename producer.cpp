#include <pthread.h>
#include <iostream>
#include "table_data.h"


using namespace std;

void *producer(void *arg) {
    int item = 1;
    for (int i = 0; i < MAX; i++) {
       
        sem_wait(&table.empty);  // Wait for an empty slot on the table

        pthread_mutex_lock(&table.lock); // Acquire the lock to access the table

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
        sem_post(&table.full);
    }
    pthread_exit(NULL);
}

int main() {
    // Initialize the synchronization variables
    sem_init(&table.empty, 0, SIZE_DATA);
    sem_init(&table.full, 0, 0);
    pthread_mutex_init(&table.lock, NULL);

    // Create the producer and consumer threads
    pthread_t prod_thd;
    pthread_create(&prod_thd, NULL, producer, NULL);

    // Wait for the threads to finish
    pthread_join(prod_thd, NULL);

    // Clean up the synchronization variables
    sem_destroy(&table.empty);
    sem_destroy(&table.full);
    pthread_mutex_destroy(&table.lock);

    return 0;
}

