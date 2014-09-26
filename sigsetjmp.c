#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include <time.h>
#include "pr_mask.h"
sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjump = 0;
static void sig_usr1(int),sig_alrm(int);
int main()
{
    if(signal(SIGALRM, sig_alrm)==SIG_ERR) {
        perror("signal(SIGALRM) error");
        return 1;
    }
    if(signal(SIGUSR1, sig_usr1)==SIG_ERR) {
        perror("signal(SIGUSR1) error");
        return 1;
    }
    pr_mask("===[main]first place:");
    if(sigsetjmp(jmpbuf, 1)) { //if return from siglongjmp
        pr_mask("===[main]returned from siglongjmp:");
        return 0;
    }
    canjump = 1;
    while(1) pause();
    return 0;
}
static void sig_alrm(int signo)
{
    pr_mask("===[sig_alrm]:");
}
static void sig_usr1(int signo)
{
    time_t starttime;
    if(canjump == 0) return;
    pr_mask("===[sig_usr1]starting:");
    alarm(3);
    starttime = time(NULL);
    while(time(NULL)<starttime+5);//busy wait for 5 seconds
    pr_mask("===[sig_usr1]finishing:");
    canjump = 0;
    siglongjmp(jmpbuf,1);
}
