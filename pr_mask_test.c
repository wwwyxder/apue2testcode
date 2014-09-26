#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "pr_mask.h"
static void sig_int(int signo)
{
    pr_mask("in sig_int:");
}
int main()
{
    struct sigaction act, oact;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGQUIT);
    act.sa_handler = sig_int;
    sigaction(SIGINT, &act, &oact);
    while(1);
    return 0;
}
