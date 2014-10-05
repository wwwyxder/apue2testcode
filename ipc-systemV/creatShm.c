#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    if(argc!=2) {
        fprintf(stderr, "usage %s <size>.\n",argv[0]);
        exit(1);
    }
    int n = atoi(argv[1]);
    int shmid = shmget(IPC_PRIVATE, n, 0666);
    if(shmid==-1) {
        perror("shmget error");
        exit(1);
    }
    return 0;
}
