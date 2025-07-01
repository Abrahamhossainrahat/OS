#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/prctl.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <number_of_children> <child_name1> <child_name2> ... <child_nameN>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0 || argc != n + 2) {
        fprintf(stderr, "Error: Number of children and provided names count mismatch or invalid.\n");
        return 1;
    }

    // Set parent process name
    prctl(PR_SET_NAME, (unsigned long)"parent_process", 0, 0, 0);
    printf("Parent process started (PID: %d)\n", getpid());

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        }

        if (pid == 0) {
            // Child process block
            // Set child's process name from argv
            prctl(PR_SET_NAME, (unsigned long)argv[i + 2], 0, 0, 0);

            printf("This is %s (PID: %d, PPID: %d)\n", argv[i + 2], getpid(), getppid());
            sleep(15); // So we can observe in pstree or top

            exit(0);
        }
        // Parent continues to fork next child
    }

    // Parent waits for all children to finish
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    printf("Parent process finished (PID: %d)\n", getpid());

    return 0;
}
