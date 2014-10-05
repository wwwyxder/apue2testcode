#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#define MAXLINE 4096
static void sig_pipe(int signo)
{
    printf("SIGPIPE caught.\n");
    exit(1);
}
int main(int argc,char *argv[])
{
    if(argc!=2) {
        fprintf(stderr,"usage %s <adder>\n",argv[0]);
        exit(1);
    }
    struct sigaction act;
    act.sa_handler = sig_pipe;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if(sigaction(SIGPIPE, &act, NULL)<0) {
        perror("set sig pipe error");
        exit(1);
    }
    int fd1[2];//p2c
    int fd2[2];//c2p
    if(pipe(fd1)<0 || pipe(fd2)<0) {
        perror("pipe fd1 fd2 error");
        exit(1);
    }
    pid_t pid = fork();
    if(pid<0) {
        perror("fork error");exit(1);
    } else if(pid>0) { //parent
        close(fd1[0]);
        close(fd2[1]);
        char line[MAXLINE];
        while(fgets(line,MAXLINE,stdin)!=NULL) {
            fprintf(stderr,"+[parent read]:%s\n",line);
            int len = strlen(line);
            if(write(fd1[1],line,len)!=len) {
                perror("write fd1[1] error"); exit(1);
            }
            fprintf(stderr,"+[parent send]:%s\n",line);
            if((len = read(fd2[0],line,MAXLINE))<0) {
                perror("read fd2[0] error"); exit(1);
            }
            if(len==0) { //pipe is close and data read is finish
                perror("read return 0 byte"); break;
            }
            line[len] = 0;
            if(fputs(line,stdout)==EOF) {
                perror("fputs error");
                exit(1);
            }
            fprintf(stderr,"+[parent recive]:%s\n",line);
            fflush(stdout);
        }
        if(ferror(stdin)) {
            perror("error on stdin");
            exit(1);
        }
        return 0;
    } else { //child
        close(fd1[1]);
        close(fd2[0]);
        if(fd1[0]!=STDIN_FILENO) {
            if(dup2(fd1[0],STDIN_FILENO)!=STDIN_FILENO) {
                perror("dup2 stdin error"); exit(1);
            }
            close(fd1[0]);
        }
        if(fd2[1]!=STDOUT_FILENO) {
            if(dup2(fd2[1],STDOUT_FILENO)!=STDOUT_FILENO) {
                perror("dup2 stdout error"); exit(1);
            }
            close(fd2[1]);
        }
        execl(argv[1],argv[1],(char*)0);
        return 0;//never reach
    }
}
