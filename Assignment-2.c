#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include<sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) { // Child process
        sleep(3); // here wait befor terminate parent 
        printf("Child: Now killing my parent (PID: %d) and child PID = %d\n", getppid(), getpid());
        kill(getppid(), SIGKILL); // terminate parent

        sleep(15); // wait such parent died
        printf("Child: My PID is %d and my PPID is %d\n", getpid(), getppid());

    } 
    else {     // Parent process
        printf("Parent: My PID is %d\n", getpid());
        pause(); // wait indefinitely for signal
    }

    return 0;
}
