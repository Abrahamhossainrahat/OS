#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

double avg ;
int max, min;

int *number;
int count;

void *average(){
    int sum = 0;
    for(int i=0;i<count;i++){
        sum +=number[i];
    }
    avg = (double)sum/ count;

    pthread_exit(0);
}

void *maximum(){
    max = number[0];
    for(int i=1;i<count;i++){
        if(number[i]>max)
            max = number[i];
    }

    pthread_exit(0);
}

void *minimum(){
    min = number[0];
    for(int i=1;i<count;i++){
        if(number[i]<min)
            min = number[i];
    }

    pthread_exit(0);
}

int main(int arg, char *argv[]){
    if(arg <2){
        fprintf(stderr, "Error : Mismatch\n");
        exit(1);
    }

    count = arg -1;
    number = (int*) malloc(count * sizeof(int));
    for(int i=0;i<count;i++){
        number[i] = atoi(argv[i+1]);
    }

    pthread_t t_avg, t_max, t_min;

    pthread_create(&t_avg, NULL, average, NULL);
    pthread_create(&t_max, NULL, maximum, NULL);
    pthread_create(&t_min, NULL, minimum, NULL);

    pthread_join(t_avg, NULL);
    pthread_join(t_max, NULL);
    pthread_join(t_min, NULL);

    printf("Average Value : %f\n", avg);
    printf("Maximun Value : %d\n", max);
    printf("Minimum Value : %d\n", min);

    free(number);
    return 0;



}