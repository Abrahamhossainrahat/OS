#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>
#include<stdlib.h>

int main()
{
    pid_t pid;

    pid = fork();
    if(pid < 0){
        perror("fork failed.\n");
        exit(1);
    }
    if(pid == 0){
        sleep(2);
        printf("Child : Now killing my parent(PID = %d ) and child PID = %d \n", getppid(), getpid());
        kill(getppid(), SIGKILL);
        sleep(5);
        printf("Child: My PID = % d and PPID = %d ",getpid(), getppid());

    }
    else{
        printf("Parent : My PID = %d\n", getpid());
        pause();
    }
}