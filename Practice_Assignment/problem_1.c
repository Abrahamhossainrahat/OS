#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/prctl.h>

int main()
{
    int a = 10, b = 5;
    pid_t pid1, pid2, pid3;
    
    prctl(PR_SET_NAME, "parent_process", 0, 0, 0);
    printf("Parent process started..... PID : %d\n", getpid());

    // Child process_1 for Addition 
    pid1 = fork();
    if(pid1 < 0){
        perror("fork1 failed");
        return 1;
    }

    if(pid1 == 0){
        printf("Child_1 (Addition) PID = %d, PPID = %d\n", getpid(), getppid());

        int sum = a + b;
        printf("Addition : %d + %d = %d\n", a, b, sum);
        return 0;
    }

    // Child Process_2 for subtraction 
    pid2 = fork();
    if (pid2 < 0){
        perror("fork2 failed. \n");
        return 1;
    }
    if(pid2 == 0){
        printf("Child_2 (Subtraction) PID = %d, PPID = %d\n", getpid(), getppid());
        int sub = a - b;
        printf("Subtraction : %d - %d = %d \n", a, b, sub);
        return 0;
    }

    // child Process_3 for Multiplication 
    pid3 = fork();
    if (pid3 < 0){
        perror("fork3 failed. \n");
        return 1;
    }
    if(pid3 == 0){
        printf("Child_3 (Multiplacation) PID = %d, PPID = %d\n", getpid(), getppid());
        int mul = a * b;
        printf("Multiplacation : %d * %d = %d \n", a, b, mul);
        return 0;
    }

    wait(NULL);
    wait(NULL);
    wait(NULL);

    printf("Parent Process finished ... PID = %d\n", getpid());


    return 0;
}