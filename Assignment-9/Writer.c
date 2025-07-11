#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    char *fifo = "myfifo";
    int fd;
    char msg[] = "Message from writer process";

    // Open the FIFO for writing
    fd = open(fifo, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    write(fd, msg, strlen(msg) + 1);
    printf("Writer sent: %s\n", msg);

    close(fd);
    return 0;
}
