#include <arpa/inet.h>
#include <sys/socket.h>
#include "unpheader.h"
void connMain(int connfd) {
    char line[MAXLINE];
    int n;
    while((n=Readline(connfd, line, MAXLINE))>0 ) {
        Writen(connfd, ")):", 3);
        Writen(connfd, line, n);
    }
}
int main()
{
    int listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(12200);
    Bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    Listen(listenfd, 32);
    while(1) {
        int connfd = Accept(listenfd, NULL, NULL);
        if(Fork()==0) { // child
            close(listenfd);
            connMain(connfd);
            exit(0);
        }
        //parent
        close(connfd);
    }
}
