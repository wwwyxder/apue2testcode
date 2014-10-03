#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
const static int N = 100000;
int num=0;
static void someOperation()
{
    int M = 10;
    int cnt = 0;
    while(cnt<M) {
        cnt+=1;
    }
}
static void *inc_thr(void *arg)
{
    for(int i=0;i<N;++i) {
        int tmp = num;
        tmp = tmp + 1;
        int t = rand()%5;
        for(int j=0;j<t;++j)
            someOperation();
        num = tmp;
    }
}
int main()
{
    srand(time(NULL));
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, inc_thr, NULL);
    pthread_create(&tid2, NULL, inc_thr, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("after add %d*2 times, num=%d\n", N, num);
    return 0;
}
