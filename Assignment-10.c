#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include<sys/wait.h>

int main() {
    char *fifo = "myfifo"; // FIFO file path
    char msg[] = "Hello from parent to child!";
    char buffer[100];
    pid_t pid;

    // Create the named pipe (FIFO)
    if (mkfifo(fifo, 0666) == -1) {
        perror("mkfifo");
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child process: read from FIFO
        int fd = open(fifo, O_RDONLY);
        if (fd == -1) {
            perror("open (child)");
            exit(1);
        }

        read(fd, buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(fd);
    } else {
        // Parent process: write to FIFO
        int fd = open(fifo, O_WRONLY);
        if (fd == -1) {
            perror("open (parent)");
            exit(1);
        }

        write(fd, msg, strlen(msg) + 1);
        printf("Parent sent: %s\n", msg);
        close(fd);

        wait(NULL); // wait for child to finish

        // Remove the FIFO
        unlink(fifo);
    }

    return 0;
}
