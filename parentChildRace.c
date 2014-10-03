#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include "TELL_WAIT_signal.h"
const static int N=10000;
const static char* path = "2xN.txt";
int main()
{
    int fd = open(path, O_CREAT|O_TRUNC|O_RDWR, 0644);
    write(fd, "0", 1);
    char inbuf[20];
    char outbuf[20];
    int num;
    TELL_WAIT();
    pid_t pid;
    pid = fork();
    if(pid<0) {
        perror("fork error");
        return 1;
    } else if(pid == 0) { //child
        for(int i=0;i<10;++i) {
            lseek(fd, 0, SEEK_SET);
            ssize_t len = read(fd, inbuf, 20);
            if(len<0) break;
            inbuf[len] = 0;
            fprintf(stderr, "CHILD read %s\n",inbuf);//debug
            sscanf(inbuf,"%d",&num);
            ++num;
            lseek(fd, 0, SEEK_SET);
            sprintf(outbuf, "%d", num);
            write(fd, outbuf, strlen(outbuf));
            fprintf(stderr, "CHILD write %s\n",outbuf);//debug
            TELL_PARENT(getppid());
            WAIT_PARENT();
        }
    } else { //parent
        for(int i=0;i<10;++i) {
            WAIT_CHILD();
            lseek(fd, 0, SEEK_SET);
            ssize_t len = read(fd, inbuf, 20);
            if(len<0) break;
            inbuf[len] = 0;
            fprintf(stderr, "PARENT read %s\n",inbuf);//debug
            sscanf(inbuf,"%d",&num);
            ++num;
            lseek(fd, 0, SEEK_SET);
            sprintf(outbuf, "%d", num);
            write(fd, outbuf, strlen(outbuf));
            fprintf(stderr, "PARENT write %s\n",outbuf);//debug
            TELL_CHILD(pid);
        }
    }
}
