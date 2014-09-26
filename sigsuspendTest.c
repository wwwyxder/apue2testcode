#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "pr_mask.h"
#include <time.h>
static volatile sig_atomic_t quitflag = 0;
static void sig_int(int signo)
{
    if(signo == SIGINT) {
        printf("[interupt]\n");
    } else if(signo == SIGQUIT) {
        printf("[quit]\n");
        quitflag = 1;
    }
}
int main()
{
    sigset_t newmask, oldmask, zeromask;
    if(signal(SIGINT, sig_int) == SIG_ERR) {
        perror("signal SIGINT error");
        return 1;
    }
    if(signal(SIGQUIT, sig_int) == SIG_ERR) {
        perror("signal SIGQUIT error");
        return 1;
    }
    sigemptyset(&newmask);
    sigemptyset(&zeromask);
    sigaddset(&newmask, SIGQUIT);
    
    time_t startTime;
    startTime = time(NULL);
    printf("start a long time task.\n");
    while(time(NULL)<startTime+5);
    printf("finish the long time task.\n");
    
    if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        perror("sigprocmask error");
        return 1;
    }
    while(quitflag == 0) {
        sigsuspend(&zeromask);
    }
    quitflag = 0;
    if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        perror("sigprocmask error");
        return 1;
    }
    return 0;
}
