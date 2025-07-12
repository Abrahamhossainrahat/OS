#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/prctl.h>

int main()
{
    pid_t pid ;
    char parent[] = "parent_process";
    prctl(PR_SET_NAME, parent, 0, 0, 0);
    printf("%s starting... PID = %d\n", parent, getpid());

    for(int i=1; i<=3;i++){
        pid = fork();
        if(pid<0){
            perror("fork failed\n");
            exit(1);
        }
        if(pid == 0){
            char name[20];
            sprintf(name,"child_%d",i);
            prctl(PR_SET_NAME, name, 0, 0, 0);
            printf("This is %s PID = %d and PPID = %d\n", name, getpid(), getppid());
            sleep(10);
            exit(0);
        }
    }
    for(int i=0;i<3;i++){
        wait(NULL);
    }
    printf("%s finished. PID = %d\n", parent, getpid());
    return 0;
    
}