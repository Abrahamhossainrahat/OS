#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define SEM_KEY 1234
#define PROCESS_COUNT 5

// semaphore wait
void sem_wait(int semid) {
    struct sembuf s = {0, -1, 0};
    semop(semid, &s, 1);
}

// semaphore signal
void sem_signal(int semid) {
    struct sembuf s = {0, 1, 0};
    semop(semid, &s, 1);
}

int main() {
    int semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);

    if (semid == -1) {
        perror("semget failed");
        exit(1);
    }

    // Initialize the semaphore to 2 (only 2 processes allowed at a time)
    semctl(semid, 0, SETVAL, 2);

    for (int i = 0; i < PROCESS_COUNT; i++) {
        if (fork() == 0) {
            printf("Process %d trying to enter critical section...\n", getpid());
            sem_wait(semid);

            printf("Process %d entered critical section\n", getpid());
            sleep(2); // simulate some task
            printf("Process %d leaving critical section\n", getpid());

            sem_signal(semid);
            exit(0);
        }
    }

    // Wait for all child processes
    for (int i = 0; i < PROCESS_COUNT; i++) {
        wait(NULL);
    }

    // Cleanup
    semctl(semid, 0, IPC_RMID);
    return 0;
}
