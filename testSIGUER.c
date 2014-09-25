#include <stdio.h>
#include <unistd.h>
#include <signal.h>
static void sig_usr(int);
int main()
{
    if(signal(SIGUSR1,sig_usr) == SIG_ERR) {
        perror("signal(SIGUSR1) error");
        return 1;
    }
    if(signal(SIGUSR2,sig_usr) == SIG_ERR) {
        perror("signal(SIGUSR2) error");
        return 1;
    }
    while(1) pause();
    return 0;
}
void sig_usr(int signo)
{
    switch(signo) {
        case SIGUSR1:
            printf("SIGUSR1 catched.\n");
            break;
        case SIGUSR2:
            printf("SIGUSR2 catched.\n");
            break;
        default:
            printf("Unexpected SIGNAL:%d\n",signo);
    }
}
