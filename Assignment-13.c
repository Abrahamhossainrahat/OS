#include <stdio.h>
#include <pthread.h>

#define NUM_ITER 1000000

int counter = 0;  // Shared variable

void* increment(void* arg) {
    for (int i = 0; i < NUM_ITER; i++) {
        counter++;  // Critical section without synchronization
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Create two threads
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Expected final value: 2 * NUM_ITER
    printf("Final counter value: %d (Expected: %d)\n", counter, 2 * NUM_ITER);

    return 0;
}
