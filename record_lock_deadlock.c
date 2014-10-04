#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include "TELL_WAIT_signal.h"
static void lockbyte(const char *msg, int fd, off_t offset)
{
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_start = offset;
    lock.l_whence = SEEK_SET;
    lock.l_len = 1;
    if(fcntl(fd, F_SETLKW, &lock)<0)
    {
        perror("fcntl set lock error");
        exit(1);
    }
    printf("%s: got the lock, byte %ld.\n", msg, offset);
}
int main()
{
    int fd = creat("tmp_file_for_record_lock_test",0644);
    if(fd<0) {
        perror("create file error");
        exit(1);
    }
    if(write(fd,"ab",2)!=2) {
        perror("write ab error");
        exit(1);
    }
    TELL_WAIT();
    pid_t pid = fork();
    if(pid<0) {
        perror("fork error");
        exit(1);
    } else if(pid==0) {//child
        lockbyte("child",fd,1);
        TELL_PARENT(getppid());
        WAIT_PARENT();
        lockbyte("child",fd,0);
    } else { //parent
        lockbyte("parent",fd,0);
        TELL_CHILD(pid);
        WAIT_CHILD();
        lockbyte("parent",fd,1);
    }
    return 0;
}
