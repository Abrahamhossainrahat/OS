#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main() {
    // Create shared memory
    int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    // Attach shared memory
    int *shared_counter = (int *)shmat(shmid, NULL, 0);
    if (shared_counter == (void *)-1) {
        perror("shmat failed");
        exit(1);
    }

    *shared_counter = 0;  // Initialize shared variable

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        for (int i = 0; i < 100000; i++) {
            (*shared_counter)++;
        }
        shmdt(shared_counter);  // Detach from child
        exit(0);
    } else {
        // Parent process
        for (int i = 0; i < 100000; i++) {
            (*shared_counter)++;
        }
        wait(NULL);  // Wait for child
        printf("Final counter value: %d\n", *shared_counter);
        shmdt(shared_counter);        // Detach from parent
        shmctl(shmid, IPC_RMID, NULL); // Remove shared memory
    }

    return 0;
}
