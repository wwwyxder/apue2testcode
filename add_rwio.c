#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAXLINE 4096
int main()
{
    char buf[MAXLINE];
    int a;
    int b;
    int len;
    while((len=read(STDIN_FILENO, buf, MAXLINE))>0) {
        buf[len] = 0;
        if(sscanf(buf,"%d%d",&a,&b)==2) {
            sprintf(buf,"%d\n",a+b);
            len = strlen(buf);
            if(write(STDOUT_FILENO, buf, len)!=len) {
                perror("write error");
                exit(1);
            }
        }  else {
            char *msg = "invalid args.\n";
            if(write(STDOUT_FILENO,msg,strlen(msg))!=strlen(msg)) {
                perror("write error");
                exit(1);
            }
        }
    }
    return 0;
}
