#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/wait.h>

int main()
{
    int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    if(shmid<0){
        perror("shmid failed\n");
        exit(1);
    }

    int *shared_counter = (int *)shmat(shmid, NULL, 0);
    if(shared_counter == (void*) -1){
        perror("shared_counter failed.\n");
        exit(1);
    }

    *shared_counter = 0;
    pid_t pid = fork();
    
    if(pid<0){
        perror("fork failed.\n");
        exit(1);
    }
    if(pid == 0){
        for(int i=0;i<100000;i++) (*shared_counter)++;
        shmdt(shared_counter);
        exit(0);
    }
    else{
        for(int i=0;i<100000;i++) (*shared_counter)++;
        wait(NULL);
        printf("Final counter : %d\n", *shared_counter);
        shmdt(shared_counter);
        shmctl(shmid, IPC_RMID, NULL);

    }
}