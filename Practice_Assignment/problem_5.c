#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/prctl.h>

int main(int arg, char *argv[]){
    if(arg < 3){
        fprintf(stderr,"User : %s <num_of_child> <child_n1>....<child_nN>\n",argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if(n<=0 || arg != n+2 ){
        fprintf(stderr, "Error : Number of children and provided names count mismatch or Invalid.\n");
        return 1;
    }

    pid_t pid;
    char parent[] = "parent_process";
    prctl(PR_SET_NAME, parent, 0, 0, 0);
    printf("%s starting... PID : %d\n",parent, getpid());

    for(int i=0; i<n;i++){
        pid = fork();
        
        if(pid<0){
            perror("fork failed");
            exit(1);
        }
        if(pid == 0){
            prctl(PR_SET_NAME, argv[i+2], 0, 0, 0);
            printf("This is %s process PID = %d and PPID = %d\n", argv[i+2], getpid(), getppid());
            sleep(10);
            exit(0);
        }
    }

    for(int i=0;i<n;i++){
        wait(NULL);
    }

    printf("%s finished. PID = %d\n", parent, getpid());
    return 0;

}