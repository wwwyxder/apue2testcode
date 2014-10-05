#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAXLINE 4096
int main()
{
    int fd[2];
    if(pipe(fd)<0) {
        perror("pipe error");
        exit(1);
    }
    pid_t pid = fork();
    if(pid<0) {
        perror("fork error");
        exit(1);
    } else if(pid>0) { //parent
        close(fd[0]);
        char buf[MAXLINE];
        //setvbuf(stdin,NULL,_IOFBF,0);
        //setvbuf(stdout,NULL,_IOFBF,0);
        FILE *file = fdopen(fd[1],"w");
        setvbuf(file,NULL,_IOFBF,0);
        while(fgets(buf,MAXLINE,stdin)!=NULL) {
            int len = strlen(buf);
            if(strcmp(buf,"quit\n")==0) break;
            printf("[parent] gets [%s]\n",buf);
            //if(fprintf(file,"%s",buf)==EOF) { //fprintf will use full buffer
            if(fputs(buf,file)==EOF) {
                perror("fputs error");
            }
            printf("[parent] write finished.\n");
        }
    } else {
        close(fd[1]);
        if(fd[0]!=STDIN_FILENO) {
            if(dup2(fd[0],STDIN_FILENO)!=STDIN_FILENO) {
                perror("dup2 error");
                exit(1);
            }
            close(fd[0]);
        }
        char buf[MAXLINE];
        //setvbuf(stdin,NULL,_IOFBF,0);
        while(fgets(buf,MAXLINE,stdin)!=NULL) {
        //while(scanf("%s",buf)==1) {
            printf("[child] gets [%s]\n",buf);
        }
    }
    return 0;
}
