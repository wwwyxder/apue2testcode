#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
static const char *Pager = "/usr/bin/less";
static const size_t MAXLINE = 4096;
int main(int argc, char *argv[])
{
    if(argc != 2) {
        fprintf(stderr,"usage %s <file name>.\n",argv[0]);
        exit(1);
    }
    FILE *fp = fopen(argv[1],"r");
    if(fp==NULL) {
        perror("fopen error");
        exit(1);
    }
    int fd[2];
    if(pipe(fd)<0) {
        perror("pipe error");
        exit(1);
    }
    pid_t pid = fork();
    if(pid<0) {
        perror("fork error");
        exit(1);
    } else if(pid==0) { //child
        close(fd[1]);
        if(fd[0]!=STDIN_FILENO) {
            if(dup2(fd[0],STDIN_FILENO)!=STDIN_FILENO) {
                perror("dup2 error");
                exit(1);
            }
            close(fd[0]);
        }
        if(execl(Pager,argv[1],"-N",(char*)0)<0) {
            perror("execl error");
            exit(1);
        }
    } else { //parent
        char line[MAXLINE];
        close(fd[0]);
        while(fgets(line, MAXLINE, fp)!=NULL) {
            int n = strlen(line);
            if(write(fd[1], line, n)!=n) {
                perror("write error to pipe");
            }
        }
        if(ferror(fp)) {
            perror("fp is error");
        }
        close(fd[1]);
        if(waitpid(pid,NULL,0)<0) {
            perror("wait error");
            exit(1);
        }
    }
    return 0;
}
