#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
    //int fd = open("afile",O_WRONLY|O_CREAT|O_TRUNC, 0666);
    //write(fd, "hello", 5);
    FILE *r = fopen("alink","r");
    FILE *w = fopen("alink","w");
    fprintf(w,"hi");
    fflush(w);

    return 0;
}
