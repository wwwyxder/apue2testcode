#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "TELL_WAIT_pipe.h"
int fd_p2c[2];
int fd_c2p[2];
void TELL_WAIT()
{
    if(pipe(fd_p2c)<0 || pipe(fd_c2p)<0) {
        perror("TELL_WAIT_pipe pipe() error");
        exit(1);
    }
}
void TELL_PARENT(pid_t pid)
{
    if(write(fd_c2p[1],"c",1)!=1) {
        perror("write error in TELL PARENT");
    }
}
void TELL_CHILD(pid_t pid)
{
    if(write(fd_p2c[1],"p",1)!=1) {
        perror("write error in TELL CHILD");
    }
}
void WAIT_PARENT()
{
    char c;
    if(read(fd_p2c[0],&c,1)!=1) {
        perror("read error in WAIT PARENT");
    }
    if(c!='p') {
        fprintf(stderr,"incorrect data in WAIT_PARENT.\n");
        exit(1);
    }
}
void WAIT_CHILD()
{
    char c;
    if(read(fd_c2p[0],&c,1)!=1) {
        perror("read error in WAIT CHILD");
    }
    if(c!='c') {
        fprintf(stderr,"incorrect data in WAIT_CHILD.\n");
        exit(1);
    }
}
