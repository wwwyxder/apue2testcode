#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
void sig_int(int signo)
{
    printf("[thread %u]SIG_INT caught.\n",(unsigned int)pthread_self());
}
void *thr(void *arg)
{
    printf("[thread %u] starting.\n",(unsigned int)pthread_self());
    sleep(2);
    printf("[thread %u] finishing.\n",(unsigned int)pthread_self());
}
void *waiting_thr(void *arg)
{
    printf("[thread %u](waiting) starting.\n",(unsigned int)pthread_self());
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    int n;
    sigwait(&set,&n);
    printf("[thread %u](waiting) finishing.\n",(unsigned int)pthread_self());
}
int main()
{
    struct sigaction act;
    act.sa_handler = sig_int;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);
    pthread_t tid1, tid2, wtid;
    pthread_create(&wtid, NULL, waiting_thr, (void*)0);
    pthread_create(&tid1, NULL, thr, (void*)0);
    pthread_create(&tid2, NULL, thr, (void*)0);
    sleep(1);
    sigset_t msk;
    sigemptyset(&msk);
    sigaddset(&msk, SIGINT);
    pthread_sigmask(SIG_BLOCK, &msk, NULL);
    kill(getpid(),SIGINT);
    pthread_join(tid1, NULL);
    pthread_join(wtid, NULL);
    pthread_join(tid2, NULL);
    return 0;
}
