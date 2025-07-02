#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Global variables to store results
double average;
int minimum;
int maximum;

// Array of numbers and its size
int *numbers;
int count;

// Thread functions
void *calculate_average(void *arg) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += numbers[i];
    }
    average = (double)sum / count;
    pthread_exit(0);
}

void *calculate_minimum(void *arg) {
    minimum = numbers[0];
    for (int i = 1; i < count; i++) {
        if (numbers[i] < minimum)
            minimum = numbers[i];
    }
    pthread_exit(0);
}

void *calculate_maximum(void *arg) {
    maximum = numbers[0];
    for (int i = 1; i < count; i++) {
        if (numbers[i] > maximum)
            maximum = numbers[i];
    }
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s number1 number2 ...\n", argv[0]);
        return 1;
    }

    count = argc - 1;
    numbers = (int *)malloc(count * sizeof(int));
    for (int i = 0; i < count; i++) {
        numbers[i] = atoi(argv[i + 1]);
    }

    pthread_t tid_avg, tid_min, tid_max;

    // Create threads
    pthread_create(&tid_avg, NULL, calculate_average, NULL);
    pthread_create(&tid_min, NULL, calculate_minimum, NULL);
    pthread_create(&tid_max, NULL, calculate_maximum, NULL);

    // Wait for threads to complete
    pthread_join(tid_avg, NULL);
    pthread_join(tid_min, NULL);
    pthread_join(tid_max, NULL);

    // Output results
    printf("A. The average value is %.2f\n", average);
    printf("B. The minimum value is %d\n", minimum);
    printf("C. The maximum value is %d\n", maximum);

    free(numbers);
    return 0;
}
