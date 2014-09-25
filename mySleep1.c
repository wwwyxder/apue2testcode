#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
static jmp_buf jmpbuf;
static void sig_alarm(int signo)
{
    longjmp(jmpbuf,1);
}
static void sig_int(int signo)
{
    volatile long k;
    printf("\nsig_int() started.\n");
    int N=50000;
    for(volatile int i=0;i<N;++i) {
        for(volatile int j=0;j<N;++j) {
            k+=i*j;
        }
        if(i%(N/10)==0) {
            printf("%d%%",i/(N/100));
            fflush(stdout);
        } else if(i%(N/100)==0) {
            printf(".");
            fflush(stdout);
        }
    }
    printf("\nsig_int() finished.\n");
}
static unsigned int mySleep(unsigned int nsecs)
{
    if(signal(SIGALRM,sig_alarm)==SIG_ERR) {
        return nsecs;
    }
    if(setjmp(jmpbuf)==0) {
        alarm(nsecs);
        pause();
    }
    return (alarm(0));
}
int main()
{
    if(signal(SIGINT,sig_int)==SIG_ERR) {
        perror("signal(SIGINT) error");
        return 1;
    }
    unsigned int unsleep = mySleep(5);
    printf("\nmySleep returned: %d unsleep.\n",unsleep);
    return 0;
}
