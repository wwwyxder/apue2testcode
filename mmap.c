#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
int main()
{
    int fd = open("hw",O_RDWR);
    char *start = (char*)mmap(0, 10, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(start == MAP_FAILED) {
        perror("mmap error");
        return 1;
    }
    start[0] = '_';
    close(1);
    return 0;
}
