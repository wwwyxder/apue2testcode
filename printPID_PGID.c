#include <stdio.h>
#include <unistd.h>
int main()
{
    printf("pid=%d, pgid=%d, sid=%d\n",getpid(),getpgid(0),getsid(0));
    return 0;
}
