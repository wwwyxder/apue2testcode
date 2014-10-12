#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
static void print_w(int sockfd)
{
    char buf[4096];
    int n;
    while((n=recv(sockfd, buf, 4096, 0))>0) {
        write(STDOUT_FILENO, buf, n);
    }
    if(n<0) {
        perror("recv error");
    }
}
int main(int argc, char* argv[])
{
    if(argc!=3) {
        printf("usage : %s <peer host ip> <peer port>\n",argv[0]);
        exit(1);
    }
    uint16_t peer_port;
    uint32_t peer_addr;
    sscanf(argv[2],"%d",&peer_port);
    peer_port = htons(peer_port);
    if(inet_pton(AF_INET, argv[1], &peer_addr)!=1) {
        perror("inet_pton error");exit(1);
    }
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = peer_addr;
    server_addr.sin_port = peer_port;
    memset(server_addr.sin_zero, 0, sizeof(server_addr.sin_zero));
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd==-1) {
        perror("make socket error"); exit(1);
    }
    if(connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr))==-1) {
        perror("connet error"); exit(1);
    }
    print_w(sockfd);
    return 0;
}
