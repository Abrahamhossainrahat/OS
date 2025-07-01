#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/prctl.h>
#include <string.h>

int main() {
    prctl(PR_SET_NAME, (unsigned long)"parent_process", 0, 0, 0);

    for (int i = 1; i <= 3; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // child process block
            char name[16];
            sprintf(name, "child_%d", i);  // child_1, child_2, child_3
            prctl(PR_SET_NAME, (unsigned long)name, 0, 0, 0);

            printf("This is %s (PID: %d, PPID: %d)\n", name, getpid(), getppid());

            sleep(15); // so that we can observe in top or pstree
            exit(0);
        }
    }

    // parent waits for all children
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    printf("Parent process finished (PID: %d)\n", getpid());
    return 0;
}
