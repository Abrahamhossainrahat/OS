#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int counter = 0;                    // shared variable
pthread_mutex_t lock;              // mutex lock

void* increment(void* arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&lock);     // lock before accessing shared resource
        counter++;
        pthread_mutex_unlock(&lock);   // unlock after done
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // initialize the mutex
    pthread_mutex_init(&lock, NULL);

    // create two threads
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    // wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // destroy the mutex
    pthread_mutex_destroy(&lock);

    // print final counter value
    printf("Final counter value: %d\n", counter);

    return 0;
}
