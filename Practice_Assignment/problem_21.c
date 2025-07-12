#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int *fib;
int n;

void *fibonacci_generate(){
    if(n>=1) fib[0] = 0;
    if(n>=2) fib[1] = 1;
    for(int i=2;i<n;i++){
        fib[i] = fib[i-1] + fib[i-2];
    }
    pthread_exit(NULL);
}

int main(int arg, char *argv[])
{
    if(arg != 2){
        fprintf(stderr, "Error : Mismatch.\n");
        exit(1);
    }

    n = atoi(argv[1]);
    if(n<0){
        printf("Please Enter the Positive number .\n");
        return 1;
    }

    fib = (int*) malloc(n * sizeof(int));

    pthread_t td;
    pthread_create(&td, NULL, fibonacci_generate, NULL);

    pthread_join(td, NULL);

    printf("Fibonacchi of %d : ",n);
    for(int i=0;i<n;i++){
        printf("%d ",fib[i]);
    }
    printf("\n");
    free(fib);
    return 0;
}