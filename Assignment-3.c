#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // 👶 Child process
        printf("Child: I am the child process. PID: %d\n", getpid());
        exit(0);  // child is dying after finishing the work.
    } else {
        // 👨‍👦 Parent process
        printf("Parent: I am the parent process. PID: %d\n", getpid());
        printf("Parent: My child (PID: %d) has finished. But I won't call wait()!\n", pid);

        // Parent sleep but not wait() so child zombie!
        sleep(30);  // সময় দাও যাতে zombie দেখা যায় ps/top দিয়ে
    }

    return 0;
}
