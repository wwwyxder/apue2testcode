#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    int mid = msgget(IPC_PRIVATE, 0644);
    if(mid==-1) {
        perror("msgget IPC_PRIVATE error");
        exit(1);
    }
    printf("message queue created. message id = %d.\n",mid);
    return 0;
}
