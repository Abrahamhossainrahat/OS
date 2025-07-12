#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int counter = 0;
pthread_mutex_t lock;

void *incement(){
    for(int i=0;i<100000;i++){
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2;

    pthread_mutex_init(&lock , NULL);

    pthread_create(&t1,NULL, incement, NULL);
    pthread_create(&t2,NULL, incement, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);

    printf("Final Counter : %d\n", counter);

    return 0;
}