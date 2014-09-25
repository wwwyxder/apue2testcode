#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
    int fd = open("/dev/tty",O_RDWR);
    write(fd,"hello~\n",7);
    return 0;
}
