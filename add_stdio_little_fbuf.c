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
    void *inbuf = malloc(128);
    void *outbuf = malloc(128);
    if(setvbuf(stdin,(char*)inbuf,_IOFBF,128)!=0) {
        perror("set stdin IOFBF error"); exit(1);
    }
    if(setvbuf(stdout,(char*)outbuf,_IONBF,128)!=0) {
        perror("set stdout IOFBF error"); exit(1);
    }
    while(fgets(buf,MAXLINE,stdin)!=NULL) {
        fprintf(stderr,"+[child read]:%s\n",buf);
        if(sscanf(buf,"%d%d",&a,&b)==2) {
            if(printf("[%d]\n",a+b)==EOF) {
                perror("printf error");
                exit(1);
            }
            fprintf(stderr,"+[child write]:[%d]\n",a+b);
        }  else {
            char *msg = "invalid args.\n";
            if(printf("%s",msg)==EOF) {
                perror("printf error");
                exit(1);
            }
            fprintf(stderr,"+[child write]:%s\n",msg);
        }
    }
    return 0;
}
