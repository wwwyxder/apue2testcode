#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
int main()
{
    pid_t pid;
    if((pid=fork())<0) {
        perror("fork error");
        return 1;
    } else if(pid == 0) { //child
        int exe_ret = 
            execl("./testinterp","testINTERP","ARG1","arg 2",(char*)0);
        if(exe_ret<0) {
            perror("execl error");
            return 1;
        }
    } else { //parent
        if(waitpid(pid,NULL,0) < 0) {
            perror("waitpid error");
            return 1;
        }
    }
}
