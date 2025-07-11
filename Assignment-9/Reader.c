#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char *fifo = "myfifo";
    int fd;
    char buf[100];

    // Open the FIFO for reading
    fd = open(fifo, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    read(fd, buf, sizeof(buf));
    printf("Reader received: %s\n", buf);

    close(fd);
    return 0;
}
