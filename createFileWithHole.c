#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main()
{
    int fd;
    if((fd=open("file.hole",O_WRONLY|O_CREAT|O_TRUNC,0644)) < 0) {
        perror("create error");
        return 1;
    }
    if(write(fd,buf1,strlen(buf1)) != strlen(buf1)) {
        perror("write buf1 error");
        return 1;
    }
    if(lseek(fd,106558,SEEK_CUR) == -1) {
        perror("seek error");
        return 1;
    }
    if(write(fd,buf2,strlen(buf2)) != strlen(buf2)) {
        perror("write buf2 error");
        return 1;
    }
    close(fd);
    return 0;
}
