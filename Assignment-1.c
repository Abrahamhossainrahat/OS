#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

int main(){
    int a = 10, b = 5;
    pid_t pid1, pid2, pid3;
    printf("Parent process started.... PID = %d\n", getpid());

    pid1 = fork();  // for first child 
    if(pid1<0){
        perror("fork1 failed\n");
        return 1;
    }
    if(pid1 == 0){
        printf("Child 1 (Addition) PID = %d, Parent PID = %d\n", getpid(), getppid());
        int sum = a+b;
        printf("Addition : %d + %d = %d\n", a,b,sum);
        return 0;
    }


    pid2 = fork();  // for second child 
    if(pid1<0){
        perror("fork1 failed\n");
        return 1;
    }
    if(pid2 == 0){
        printf("Child 2 (Subtraction) PID = %d, Parent PID = %d\n", getpid(), getppid());
        int sub = a-b;
        printf("Subtraction : %d - %d = %d\n", a,b,sub);
        return 0;
    }

    
    pid3 = fork();  // for third child 
    if(pid1<0){
        perror("fork1 failed\n");
        return 1;
    }
    if(pid3 == 0){
        printf("Child 3 (Multiplication) PID = %d, Parent PID = %d\n", getpid(), getppid());
        int mul = a*b;
        printf("Multiplication : %d * %d = %d\n", a,b,mul);
        return 0;
    }

    wait(NULL);
    wait(NULL); 
    wait(NULL);
    printf("Parent Process (PID = %d) finished.\n", getpid());
    return 0;





   

}