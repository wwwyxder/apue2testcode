#include "TELL_WAIT_signal.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
static volatile sig_atomic_t sigflag = 0;
static sigset_t newmask, oldmask, zeromask;
void sig_usr(int signo)
{
    sigflag = 1;
}
void TELL_WAIT()
{
    if(signal(SIGUSR1, sig_usr)==SIG_ERR) {
        perror("signal SIGUSR1 error");
        exit(1);
    }
    if(signal(SIGUSR2, sig_usr)==SIG_ERR) {
        perror("signal SIGUSR2 error");
        exit(1);
    }
    sigemptyset(&newmask);
    sigemptyset(&zeromask);
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);
    if(sigprocmask(SIG_BLOCK, &newmask, &oldmask ) < 0) {
        perror("sigprocmask SIG_BLOCK error");
        exit(1);
    }
}
// SIGUSR1 for parent -> child
// SIGUSR2 for child -> parent
void TELL_CHILD(pid_t pid)
{
    kill(pid, SIGUSR1);
}
void TELL_PARENT(pid_t pid)
{
    kill(pid, SIGUSR2);
}
void WAIT_CHILD()
{
    while(sigflag == 0) {
        sigsuspend(&zeromask);
    }
    sigflag = 0;
    if(sigprocmask(SIG_BLOCK, &oldmask, NULL)<0) {
        perror("reset sigpromask error in WAIT_CHILD()");
        exit(1);
    }
}
void WAIT_PARENT()
{
    while(sigflag == 0 ) {
        sigsuspend(&zeromask);
    }
    sigflag = 0;
    if(sigprocmask(SIG_BLOCK, &oldmask, NULL)<0) {
        perror("reset sigpromask error in WAIT_PARENT()");
        exit(1);
    }
}
