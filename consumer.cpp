#include <pthread.h>
#include <iostream>
#include "table_data.h"

using namespace std;

void *consumer(void *arg) {
    for (int i = 0; i < MAX; i++) {
        
        sem_wait(&table.full); // Wait for a full slot on the table
        pthread_mutex_lock(&table.lock); // Acquire the lock

        // Take an item off the table
        for (int j = 0; j < SIZE_DATA; j++) {
            if (table.items[j] != 0) {
                int item = table.items[j];
                table.items[j] = 0;
                cout << "Consumed item " << item << endl;
                break;
            }
        }

        // Release the lock and let the slot know it is empty
        pthread_mutex_unlock(&table.lock);
        sem_post(&table.empty);
    }
    pthread_exit(NULL);
}

int main() {
    // Initialize the synchronization variables
    sem_init(&table.empty, 0, SIZE_DATA);
    sem_init(&table.full, 0, 0);
    pthread_mutex_init(&table.lock, NULL);

    // consumer threads
    pthread_t cons_thd;
    pthread_create(&cons_thd, NULL, consumer, NULL);

    // Wait for the threads to finish
       pthread_join(cons_thd, NULL);

    // Clean up the synchronization variables
    sem_destroy(&table.empty);
    sem_destroy(&table.full);
    pthread_mutex_destroy(&table.lock);

    return 0;
}

