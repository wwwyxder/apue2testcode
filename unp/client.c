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
void doit_select(FILE* file, int sockfd)
{
    char sendLine[MAXLINE];
    char recvLine[MAXLINE];
    int maxfdp1;
    int stdin_eof = 0;
    fd_set read_set;
    while(1) {
        FD_ZERO(&read_set);
        if(!stdin_eof)
            FD_SET(fileno(file), &read_set);
        FD_SET(sockfd, &read_set);
        maxfdp1 = myMax(fileno(file),sockfd)+1;
        Select(maxfdp1, &read_set, NULL, NULL, NULL);
        if(FD_ISSET(sockfd,&read_set)) {
            int n= Readline(sockfd, recvLine, MAXLINE);
            if(n==0) {
                if(stdin_eof) {
                    return ;//works all done
                }
                fprintf(stderr, "doit(): server terminated permaturely.\n");
                exit(1);
            }
            Fputs(recvLine,stdout);
        }
        if(FD_ISSET(fileno(file),&read_set)) {
            if(Fgets(sendLine, MAXLINE, stdin)==NULL) {
                stdin_eof = 1;
                shutdown(sockfd, SHUT_WR);
                continue;
            }
            Writen(sockfd, sendLine, strlen(sendLine));
        }
    }
}
int main(int argc, char *argv[])
{
    if(argc!=2) {
        fprintf(stderr, "usage : %s <server ip>\n", argv[0]);
        exit(1);
    }
    int clifd[1];
    for(int i=0;i<1;++i) {
        clifd[i] = Socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in servaddr;
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
        servaddr.sin_port = htons(12200);
        Connect(clifd[i], (struct sockaddr*)&servaddr, sizeof(servaddr));
    }
    doit_select(stdin, clifd[0]);
    return 0;
}
