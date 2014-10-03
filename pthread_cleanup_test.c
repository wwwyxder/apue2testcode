#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
struct params
{
    int exec;
    char msg[64];
};
static void cleanup(void *arg)
{
    printf("[cleanup]%s\n",(char*)arg);
}
static void *thr(void *arg)
{
    struct params p = *(struct params*)arg;
    pthread_cleanup_push(cleanup, "first one.");
    pthread_cleanup_push(cleanup, "second one.");
    printf("push completed.[%s]\n",p.msg);
    if(p.exec!=0)
        pthread_exit((void*)0);
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    pthread_exit((void*)0);
}
int main()
{
    struct params p1;
    struct params p2;
    p1.exec = 0;
    strncpy(p1.msg,"p1,no exec.", 64);
    p2.exec = 1;
    strncpy(p2.msg,"p2,exec.", 64);
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, thr, &p1);
    pthread_create(&tid2, NULL, thr, &p2);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}
