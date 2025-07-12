#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>

int main()
{
    char *fifo = "my_fifo";
    int fd;
    char writer_msg[] = "Hello from writer";

    mkfifo(fifo, 0666);

    fd = open(fifo, O_WRONLY);

    if(fd == -1){
        perror("File open failed");
        exit(1);
    }

    write(fd, writer_msg, strlen(writer_msg)+1);
    printf("Writer Send : %s\n", writer_msg);
    close(fd);
    unlink(fifo);

    return 0;

}