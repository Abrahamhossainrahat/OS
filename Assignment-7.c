#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/types.h>
int global_var = 10; // Global variable

int main() {
    int local_var = 20; // Local variable

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        global_var += 5;
        local_var += 5;
        printf("Child Process:\n");
        printf("PID: %d, PPID: %d\n", getpid(), getppid());
        printf("Global Variable: %d\n", global_var);
        printf("Local Variable: %d\n\n", local_var);
    } else {
        // Parent process
        sleep(1); // Ensure child prints first
        global_var -= 5;
        local_var -= 5;
        printf("Parent Process:\n");
        printf("PID: %d\n", getpid());
        printf("Global Variable: %d\n", global_var);
        printf("Local Variable: %d\n", local_var);
    }

    return 0;
}
