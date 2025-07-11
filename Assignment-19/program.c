#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

void *thread_func(void *arg) {
    printf("Thread %ld is running in process %d\n", (long)arg, getpid());
    sleep(3); // to keep thread alive
    return NULL;
}

int main() {
    pthread_t t1, t2;

    printf("Main process PID: %d\n", getpid());

    // Create two threads
    pthread_create(&t1, NULL, thread_func, (void *)1);
    pthread_create(&t2, NULL, thread_func, (void *)2);

    sleep(1); // ensure threads have started

    // ------------ A. fork() from a thread ------------
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        printf("\n[A] In child process after fork()\n");
        printf("Child PID: %d, PPID: %d\n", getpid(), getppid());

        // See how many threads are active
        sleep(5); // allow time for threads to finish if not duplicated
        printf("Child exiting...\n");
        exit(0);
    } else {
        // Parent process waits
        wait(NULL);
    }

    // ------------ B. exec() from a thread ------------
    pid = fork();
    if (pid == 0) {
        printf("\n[B] In child process before exec()\n");
        execlp("ls", "ls", "-l", NULL); // this replaces whole process image
        perror("execlp failed");
        exit(1);
    } else {
        wait(NULL);
    }

    // ------------ C. exec() immediately after fork() ------------
    pid = fork();
    if (pid == 0) {
        printf("\n[C] In child process (forked), now calling exec()\n");
        execlp("echo", "echo", "Exec replaces process code!", NULL);
        perror("exec failed");
        exit(1);
    } else {
        wait(NULL);
    }

    // Join threads (though exec replaces them if called earlier)
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("\nMain process exiting.\n");
    return 0;
}
