#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
static void pr_ids(char* name)
{
    printf("%s: pid=%d, ppid=%d, pgrp=%d, tpgrp=%d\n",name,getpid(),getppid(),getpgrp(),tcgetpgrp(STDIN_FILENO));
}
static void sig_hup(int signo)
{
    printf("SIGHUP catched. pid=%d\n",getpid());
}
int main()
{
    char c;
    pid_t pid;
    pr_ids("parent");
    pid = fork();
    if(pid < 0) {
        perror("fork error");
        return 1;
    } else if(pid>0) { //parent
        sleep(5);
        return 0;
    } else { //child
        pr_ids("child");
        signal(SIGHUP,sig_hup);
        kill(getpid(),SIGTSTP);
        pr_ids("child");//print after wake up from TSTP
        if(read(STDIN_FILENO,&c,1)!=1) {
            perror("read error");
        }
        return 0;
    }
}
