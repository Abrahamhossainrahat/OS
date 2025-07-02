#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<sys/wait.h>
#include<sys/types.h>

int main() {
    int pipefd[2]; // pipefd[0] = read end, pipefd[1] = write end
    pid_t pid;
    char write_msg[] = "Hello from parent!";
    char read_msg[100];

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        close(pipefd[1]); // Close unused write end

        read(pipefd[0], read_msg, sizeof(read_msg)); // Read from pipe
        printf("Child received: %s\n", read_msg);

        close(pipefd[0]); // Close read end
    } else {
        // Parent process
        close(pipefd[0]); // Close unused read end

        write(pipefd[1], write_msg, strlen(write_msg) + 1); // Write to pipe
        printf("Parent sent: %s\n", write_msg);

        close(pipefd[1]); // Close write end
        wait(NULL); // Wait for child to finish
    }

    return 0;
}
