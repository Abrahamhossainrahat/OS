#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define SHM_KEY 1234
#define SEM_KEY 5678

// semaphore operations
void sem_wait(int semid) {
    struct sembuf s = {0, -1, 0};
    semop(semid, &s, 1);
}

void sem_signal(int semid) {
    struct sembuf s = {0, 1, 0};
    semop(semid, &s, 1);
}

int main() {
    int shmid, semid;
    int *counter;

    // create shared memory
    shmid = shmget(SHM_KEY, sizeof(int), IPC_CREAT | 0666);
    counter = (int *)shmat(shmid, NULL, 0);
    *counter = 0;

    // create semaphore with initial value 1
    semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    semctl(semid, 0, SETVAL, 1);

    // create 2 child processes
    for (int i = 0; i < 2; i++) {
        if (fork() == 0) {
            for (int j = 0; j < 100000; j++) {
                sem_wait(semid);    // lock
                (*counter)++;
                sem_signal(semid);  // unlock
            }
            shmdt(counter);
            exit(0);
        }
    }

    // wait for children
    wait(NULL);
    wait(NULL);

    // print final result
    printf("Final counter value: %d\n", *counter);

    // cleanup
    shmdt(counter);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);

    return 0;
}
