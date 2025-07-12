#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>

int main()
{
    char *fifo = "my_fifo";
    int fd ;
    char read_msg[100];

    mkfifo(fifo, 0666);

    fd = open(fifo, O_RDONLY);
    if(fd == -1){
        perror("file open failed\n");
        exit(1);
    }

    read(fd, read_msg, sizeof(read_msg));
    printf("Reader Received : %s\n", read_msg);
    close(fd);
    unlink(fifo);
   
    return 0;
}