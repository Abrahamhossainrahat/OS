#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *fib;  // Global array to store Fibonacci numbers
int n;     // Number of Fibonacci numbers to generate

void *generate_fibonacci(void *arg) {
    if (n >= 1) fib[0] = 0;
    if (n >= 2) fib[1] = 1;

    for (int i = 2; i < n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t tid;

    if (argc != 2) {
        printf("Usage: %s <number of Fibonacci terms>\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]); // Convert string input to integer
    if (n <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }

    fib = (int *)malloc(n * sizeof(int));
    if (fib == NULL) {
        perror("Memory allocation failed");
        return 1;
    }

    // Create a thread to generate Fibonacci sequence
    pthread_create(&tid, NULL, generate_fibonacci, NULL);

    // Wait for the thread to finish
    pthread_join(tid, NULL);

    // Print the result
    printf("Fibonacci sequence:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", fib[i]);
    }
    printf("\n");

    free(fib);
    return 0;
}
