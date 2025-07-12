#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include<sys/types.h>
#include<sys/prctl.h>

int main()
{
    pid_t pid;
    prctl(PR_SET_NAME, "parent_process",0,0,0);
    //printf("Parent : I am the parent process . My PID : %d\n", getpid());

    for(int i=1; i<=3;i++){
        pid = fork();
        if(pid == 0 ){
            char name[20];
            sprintf(name,"child_%d",i );
            prctl(PR_SET_NAME, name, 0 ,0, 0);
            printf("This is %s process PID = %d and PPID = %d\n",name,getpid(), getppid());
            sleep(10);
            exit(0);
        }
    }
    for(int i=0; i<3;i++){
        wait(NULL);
    }
    return 0;
   
}