#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>

int main()
{
    key_t key;
    key = ftok("myfile", 65);
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    if(shmid<0){
        perror("shmid failed.\n");
        exit(1);
    }
    
    int *counter =(int*) shmat(shmid, NULL, 0);
    if(counter == (void*) -1){
        perror("counter failed.\n");
        exit(1);
    }


    for(int i=0;i<1000000;i++) (*counter)++;

    printf("Final Counter : %d\n", *counter);
    shmdt(counter);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}