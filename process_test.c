#include<sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {
        printf("I am Parent. PID: %d\n", getpid());
    } else if (pid == 0) {
        printf("I am Child. PID: %d, My Parent: %d\n", getpid(), getppid());
    } else {
        printf("Fork failed.\n");
    }

    return 0;
}
