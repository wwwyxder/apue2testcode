#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

static jmp_buf read_wait_buf;
static void sig_alarm(int signo)
{
    longjmp(read_wait_buf,1);
}
int main()
{
    if(signal(SIGALRM,sig_alarm)==SIG_ERR) {
        perror("signal(SIGALARM) error");
        return 1;
    }
    if(setjmp(read_wait_buf)!=0) {
        fprintf(stderr,"read error:time out.\n");
        return 1;
    }
    alarm(5);
    char line[2048];
    int n;
    if((n=read(STDIN_FILENO,line,2048))<0) {
        fprintf(stderr,"read error.\n");
        return 1;
    }
    write(STDOUT_FILENO,line,n);
    return 0;
}
