#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/types.h>

int main()
{
    char *fifo = "my_fifo";
    int fd;
    char write_msg[] = "Hello from parent";
    char read_msg[100];

    mkfifo(fifo, 0666);

    pid_t pid = fork();

    if(pid<0){
        perror("fork failed.\n");
        exit(1);
    }
    if(pid == 0){
        fd = open(fifo, O_RDONLY);
        if(fd == -1){
            perror("file open failed.\n");
            exit(1);
        }
        read(fd, read_msg, sizeof(read_msg));
        printf("Child Receive : %s\n", read_msg);
        close(fd);
    }
    else{
        fd = open(fifo, O_WRONLY);
        if(fd == -1){
            perror("file open failed.\n");
            exit(1);
        }
        write(fd, write_msg, strlen(write_msg)+1);
        printf("Parent Send : %s\n", write_msg);
        close(fd);

        wait(NULL);
        unlink(fifo);
    }

}