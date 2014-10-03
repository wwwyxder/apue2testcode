#include "TELL_WAIT_signal.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
static void someLongTimeTask()
{
    volatile int i=1;
    volatile int sum = 0;
    while(i<100000) {
        sum += i;
        ++i;
    }
}
static void charatatime(char* str)
{
    char* p;
    setbuf(stdout, NULL);
    for(p=str;*p!=0;++p) {
        fputc(*p ,stdout);
        someLongTimeTask();
    }
}
int main()
{
    pid_t pid;
    TELL_WAIT();
    if((pid = fork())<0) {
        perror("fork error");
        exit(1);
    } else if(pid==0) { // child
        charatatime("\n[This is a cery long sentence from child process.]\n");
        TELL_PARENT(getppid());
    } else { //parent
        WAIT_CHILD();
        charatatime("\n[This is a cery long sentence from parent process.]\n");
    }
    return 0;
}

