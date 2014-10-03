#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
static void* thr1(void* arg)
{
    printf("thread 1 is running.\n");
    return (void*)1;
}
static void* thr2(void* arg)
{
    printf("thread 2 is running.\n");
    return (void*)2;
}
int main()
{
    pthread_t tid1, tid2;
    void *tret;
    if(pthread_create(&tid1, NULL, thr1, NULL)!=0) {
        perror("thread 1 create error");
        return 1;
    }
    if(pthread_create(&tid2, NULL, thr2, NULL)!=0) {
        perror("thread 2 create error");
        return 1;
    }
    if(pthread_join(tid1, &tret)!=0) {
        perror("join 1 error");
        return 1;
    }
    printf("thread 1 exit with %d\n",(int)tret);
    if(pthread_join(tid2, &tret)!=0) {
        perror("join 2 error");
        return 1;
    }
    printf("thread 2 exit with %d\n",(int)tret);
    return 0;
}
