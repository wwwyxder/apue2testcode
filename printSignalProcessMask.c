#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
int main()
{
    for(int i=SIGHUP;i<=SIGSYS;++i) {
        printf("[%2d]:%s\n",i,strsignal(i));
    }
    sigset_t set;
    sigprocmask(0,NULL,&set);
    sigaddset(&set,SIGALRM);
    for(int i=SIGHUP;i<=SIGSYS;++i) {
        if(sigismember(&set,i)) {
            printf("contains signal [%d]: %s\n",i,strsignal(i));
        }
    }
    return 0;
}
