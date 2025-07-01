#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/prctl.h>
#include <string.h>

int main() {
    // Set parent process name
    prctl(PR_SET_NAME, (unsigned long)"parent_process", 0, 0, 0);

    for (int i = 1; i <= 3; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Inside child process
            char name[20];
            sprintf(name, "child_%d", i); // child_1, child_2, child_3
            prctl(PR_SET_NAME, (unsigned long)name, 0, 0, 0);

            printf("I am %s (PID: %d, PPID: %d)\n", name, getpid(), getppid());

            sleep(15);  // So that we can observe process tree
            exit(0);
        }
    }

    // Parent waits for all child processes to finish
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    printf("Parent process (PID: %d) finished.\n", getpid());
    return 0;
}
