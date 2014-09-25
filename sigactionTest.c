#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
void sig_int(int signo) 
{
    printf("SIGINT caught.\n");
}
void sig_int3(int signo, siginfo_t* info, void* context)
{
    printf("SIGINT caught in 3.\n");
    return;
}
int main()
{
    struct sigaction act, oact;
    sigemptyset(&act.sa_mask);
    //act.sa_handler = sig_int;
    act.sa_sigaction = sig_int3;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &act, &oact);
    while(1);
    return 0;
}
