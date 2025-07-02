#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    // 1. Create shared memory
    int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    int *counter = (int *)shmat(shmid, NULL, 0);
    *counter = 0; // initialize

    pid_t p1 = fork(); // first child

    if (p1 == 0) {
        // First child process
        for (int i = 0; i < 100000; i++) {
            (*counter)++;
        }
        shmdt(counter);
        exit(0);
    } else {
        pid_t p2 = fork(); // second child

        if (p2 == 0) {
            // Second child process
            for (int i = 0; i < 100000; i++) {
                (*counter)++;
            }
            shmdt(counter);
            exit(0);
        } else {
            // Parent process waits for both
            wait(NULL);
            wait(NULL);

            printf("Final counter value: %d\n", *counter);

            // Clean up shared memory
            shmdt(counter);
            shmctl(shmid, IPC_RMID, NULL);
        }
    }

    return 0;
}
