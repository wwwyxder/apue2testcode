#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
void sig_intr(int signo)
{
    fprintf(stderr,"SIGINT caught.\n");
}
int main()
{
    struct sigaction act;
    act.sa_handler = sig_intr;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT,&act,NULL);
    fd_set s;
    FD_ZERO(&s);
    FD_SET(STDIN_FILENO,&s);
    sigset_t sigs,zero_sigs;
    sigemptyset(&sigs);
    sigemptyset(&zero_sigs);
    sigaddset(&sigs,SIGINT);
    sigprocmask(SIG_BLOCK, &sigs, NULL);
    int nready = pselect(3,&s,NULL,NULL,NULL,&zero_sigs);
    printf("nready:%d\n",nready);
}
