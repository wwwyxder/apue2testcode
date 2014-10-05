#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
    if(argc!=2) {
        fprintf(stderr,"usage: %s <nsems>\n",argv[0]);
        exit(1);
    }
    int n = atoi(argv[1]);
    int semid = semget(IPC_PRIVATE, n, 0666);
    if(semid == -1) {
        perror("semget IPC_PRIVATE error");
        exit(1);
    }
    printf("created semaphore id = %d.\n",semid);
    return 0;
}
