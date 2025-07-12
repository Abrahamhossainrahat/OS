#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int global = 10;
int main()
{
    int local = 15;
    pid_t pid = fork();

    if(pid<0){
        perror("fork failed.\n");
        return 1;
    }
    if(pid == 0){
        global += 5;
        local += 5;
        printf("Child Process:\nPID = %d and PPID = %d\n",getpid(), getppid());
        printf("Global Variable = %d\n", global);
        printf("Local Variable = %d\n\n", local);
        return 0;
    }
    else{
        sleep(2);
        global -= 5;
        local -= 5;
        printf("Parent Process:\nPID = %d\n",getpid());
        printf("Global Variable = %d\n", global);
        printf("Local Variable = %d\n", local);

    }
    return 0;
}