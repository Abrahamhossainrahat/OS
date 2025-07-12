#include<stdio.h>
#include<pthread.h>

#define N 10000
int cnt = 0;

void* increment(){
    for(int i=0;i<N;i++){
        cnt++;
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("cnt vlaue : %d and Actual value : %d\n", cnt, N*2);

    return 0;
}