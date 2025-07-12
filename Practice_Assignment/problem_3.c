#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
    pid_t pid ;
    
    pid = fork();

    if(pid<0){
        perror("fork failed.\n");
        exit(1);
    }
    if(pid ==0){
        printf("Child : I am the child process. My PID : %d\n", getpid());
        exit(0);
    }
    else{
        printf("Parent : I am the parent process. My PID : %d\n", getpid());
        printf("Parent : My child (PID = %d ) process has finished . But I won't call wait()\n",pid);
        sleep(10);
    }
}