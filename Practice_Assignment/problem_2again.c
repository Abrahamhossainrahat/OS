#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>

int main()
{
    pid_t pid;

    pid = fork();

    if(pid < 0){
        perror("fork failed.");
        exit(1);
    }

    if(pid == 0 ){
        sleep(2);
        printf("Child :Killing my Parent(PID = %d) and child = %d\n", getppid(), getpid());
        kill(getppid(), SIGKILL);
        sleep(5);
        printf("Child : My PID = %d and PPID = %d\n", getpid(), getppid());
    }
    else{
        printf("Parent : My PID = %d\n", getpid());
        pause();
    }
}
