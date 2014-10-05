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
    while(fgets(buf,MAXLINE,stdin)!=NULL) {
        if(sscanf(buf,"%d%d",&a,&b)==2) {
            if(printf("%d\n",a+b)==EOF) {
                perror("printf error");
                exit(1);
            }
        }  else {
            char *msg = "invalid args.\n";
            if(printf("%s",msg)==EOF) {
                perror("printf error");
                exit(1);
            }
        }
    }
    return 0;
}
