#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
int initserver(int type, const struct sockaddr *addr, socklen_t alen, int qlen)
{
    int err = 0;
    int fd = socket(addr->sa_family, type, 0);
    if(fd<0) return -1;
    if(bind(fd, addr, alen)<0) {
        close(fd);
        return -1;
    }
    if(type == SOCK_STREAM || type == SOCK_SEQPACKET) {
        if(listen(fd, qlen)<0) {
            close(fd);
            return -1;
        }
    }
    return fd;
}
int main()
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    u_int32_t tmp_addr;
    inet_pton(AF_INET, "127.0.0.1", &tmp_addr);
    addr.sin_addr.s_addr = tmp_addr;//htonl(tmp_addr);
    addr.sin_port = 1220;
    memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));
    int fd = initserver(AF_INET, (struct sockaddr*)&addr, sizeof(struct sockaddr_in),128);
    if(fd<0) {
        perror("initial server error.\n");
        exit(1);
    }
    printf("initial server success.\n");
    
    return 0;
}
