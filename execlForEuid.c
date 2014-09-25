#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
int main()
{
    int fd;
    printf("uid=%d\ngid=%d\neuid=%d\negid=%d\n",getuid(),getgid(),geteuid(),getegid());
    execl("./printIDsNoSetUID","./printIDsNoSetUID",(char*)0);
    return 0;
}
