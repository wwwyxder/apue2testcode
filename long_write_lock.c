#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
static void set_fl(int fd, int flag)
{
    int val;
    if((val=fcntl(fd, F_GETFL, 0))<0) {
        perror("fcntl GETFL error");
        exit(1);
    }
    val |= flag;
    if(fcntl(fd, F_SETFL, val)<0) {
        perror("fcntl SETFL error");
        exit(1);
    }
}
static void clr_fl(int fd, int flag)
{
    int val;
    if((val=fcntl(fd, F_GETFL, 0))<0) {
        perror("fcntl GETFL error");
        exit(1);
    }
    val &= ~flag;
    if(fcntl(fd, F_SETFL, val)<0) {
        perror("fcntl SETFL error");
        exit(1);
    }
}
char buf[500000];
int main()
{
    for(int i=0;i<500000;++i) {
        buf[i] = 'a';
    }
    buf[499999] = 0;
    int ntowrite=499999, nwrite;
    char *ptr=buf;
    set_fl(STDOUT_FILENO, O_NONBLOCK);
    while(ntowrite>0) {
        errno = 0;
        nwrite = write(STDOUT_FILENO, ptr, ntowrite);
        fprintf(stderr, "nwrite = %d, errno = %d",nwrite, errno);
        if(errno!=0) perror(""); else fprintf(stderr,"\n");
        if(nwrite>0) {
            ntowrite -= nwrite;
            ptr += nwrite;
        }
    }
    clr_fl(STDOUT_FILENO, O_NONBLOCK);
    return 0;
}
