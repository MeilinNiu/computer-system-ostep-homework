#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2
#define NUM_INCREMENTS 10000000

// Shared variable
volatile int counter = 0;

// Mutex to control access to the critical section
pthread_mutex_t lock;

// Thread function to increment counter
void *increment_counter(void *threadid) {
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        // Entering critical section (race condition can occur if no lock)
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
        // Leaving critical section
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;

    // Initialize the mutex
    pthread_mutex_init(&lock, NULL);

    // Create threads
    for (long t = 0; t < NUM_THREADS; t++) {
        rc = pthread_create(&threads[t], NULL, increment_counter, (void *)t);
        if (rc) {
            printf("Error: Unable to create thread %ld\n", t);
            exit(-1);
        }
    }

    // Join threads
    for (long t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    // Print the final value of the counter
    printf("Final value of counter: %d\n", counter);

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    return 0;
}