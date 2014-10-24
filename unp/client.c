#include <arpa/inet.h>
#include <sys/socket.h>
#include "unpheader.h"
void doit(int sockfd)
{
    char sendLine[MAXLINE];
    char recvLine[MAXLINE];
    while(Fgets(sendLine, MAXLINE, stdin)!=NULL) {
        Writen(sockfd, sendLine, strlen(sendLine));
        int n = Readline(sockfd, recvLine, MAXLINE);
        if(n==0) {
            fprintf(stderr,"doit():server terminated permaturely.\n");
            exit(1);
        }
        Fputs(recvLine,stdout);
    }
}
int main(int argc, char *argv[])
{
    if(argc!=2) {
        fprintf(stderr, "usage : %s <server ip>\n", argv[0]);
        exit(1);
    }
    int clifd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    servaddr.sin_port = htons(12200);
    Connect(clifd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    doit(clifd);
    return 0;
}
