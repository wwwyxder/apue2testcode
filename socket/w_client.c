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
    if(argc!=4) {
        printf("usage : %s <local port> <peer host ip> <peer port>\n",argv[0]);
        exit(1);
    }
    uint16_t local_port;
    uint32_t local_addr;
    uint16_t peer_port;
    uint32_t peer_addr;
    sscanf(argv[1],"%d",&local_port);
    local_port = htons(local_port);
    if(inet_pton(AF_INET, "127.0.0.1", &local_addr)!=1) {
        perror("inet_pton error");exit(1);
    }
    sscanf(argv[3],"%d",&peer_port);
    peer_port = htons(peer_port);
    if(inet_pton(AF_INET, argv[2], &peer_addr)!=1) {
        perror("inet_pton error");exit(1);
    }
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = local_addr;
    myaddr.sin_port = local_port;
    memset(myaddr.sin_zero, 0, sizeof(myaddr.sin_zero));
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = peer_addr;
    server_addr.sin_port = peer_port;
    memset(server_addr.sin_zero, 0, sizeof(server_addr.sin_zero));
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd==-1) {
        perror("make socket error"); exit(1);
    }
    if(bind(sockfd, (struct sockaddr*)&myaddr, sizeof(myaddr))==-1) {
        perror("bind error");exit(1);
    }
    if(connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr))==-1) {
        perror("connet error"); exit(1);
    }
    print_w(sockfd);
    return 0;
}
