#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
int main()
{
    int fd;
    printf("uid=%d\ngid=%d\neuid=%d\negid=%d\n",getuid(),getgid(),geteuid(),getegid());
    if((fd=open("fileForIDs.test",O_RDWR))==-1) {
        perror("open error");
        return 1;
    }
    printf("open success.\n");
    return 0;
}
