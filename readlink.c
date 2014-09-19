#include <stdio.h>
#include <unistd.h>
int main(int argc,char* argv[])
{
    char buf[4096];
    int len;
    if(argc!=2) {
        fprintf(stderr,"usage:readlink <link name>\n");
        return 1;
    }
    len = readlink(argv[1],buf,4096);
    if(len==-1) {
        perror("readlink error");
        return 1;
    }
    buf[len] = 0;
    printf("%s:%s",argv[1],buf);
    return 0;
}
