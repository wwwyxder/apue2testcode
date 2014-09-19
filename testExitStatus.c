#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
extern void printExitStatus(int);
int main()
{
    pid_t pid;
    int status;
    //-------------------  1  ----------------------------
    if((pid = fork()) < 0) {
        perror("fork error");
        return 1;
    } else if(pid == 0) {
        exit(7);
    }
    if(wait(&status) != pid) {
        perror("wait error");
        return 1;
    }
    printExitStatus(status);
    
    //-------------------  2  ----------------------------
    if((pid = fork()) < 0) {
        perror("fork error");
        return 1;
    } else if(pid == 0) {
        abort();
    }
    if(wait(&status) != pid) {
        perror("wait error");
        return 1;
    }
    printExitStatus(status);
    //-------------------  3  ----------------------------
    if((pid = fork()) < 0) {
        perror("fork error");
        return 1;
    } else if(pid == 0) {
        status /=0;
    }
    if(wait(&status) != pid) {
        perror("wait error");
        return 1;
    }
    printExitStatus(status);

    return 0;
}
