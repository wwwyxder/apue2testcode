#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
static void printIDs(const char *str)
{
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    printf("%s pid=%u tid=%u/0x%x/0%o\n",str,(unsigned int)pid, (unsigned int)tid, (unsigned int)tid, (unsigned int)tid);
}
static void* thr(void* arg)
{
    printIDs(" new thread:");
    return (void*)0;
}
int main()
{
    pthread_t ntid;
    int err = pthread_create(&ntid, NULL, thr, NULL);
    if(err!=0) {
        perror("pthread_create error");
        return 1;
    }
    printIDs("main thread:");
    sleep(1);
    return 0;
}
