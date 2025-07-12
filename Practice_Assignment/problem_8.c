#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>

int main()
{
    pid_t pid;
    int pipefd[2];
    char write_msg[] = "Hello child";
    char read_msg[20];

    if(pipe(pipefd) == -1){
        perror("Pipe creation failed.\n");
        exit(1);
    }

    pid = fork();
    if(pid<0){
        perror("fork failed\n");
        exit(1);
    }

    if(pid == 0){
        close(pipefd[1]);
        read(pipefd[0],read_msg, sizeof(read_msg));
        printf("Receive : %s\n", read_msg);
        close(pipefd[0]);
        exit(0);
    }
    else{
        close(pipefd[0]);
        write(pipefd[1], write_msg, strlen(write_msg)+1);
        printf("Send : %s\n", write_msg);
        close(pipefd[1]);
        wait(NULL);
    }
    return 0;

}