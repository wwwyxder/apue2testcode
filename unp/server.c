#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "unpheader.h"
void connMain(int connfd) {
    char line[MAXLINE];
    int n;
    while((n=Readline(connfd, line, MAXLINE))>0 ) {
        Writen(connfd, ")):", 3);
        Writen(connfd, line, n);
    }
}
void addn(char* sum, const char *numbers, size_t n)
{
    long x,y;
    if(sscanf(numbers, "%ld%ld", &x, &y)!=2) {
        snprintf(sum, n, "input format error\n");
    } else {
        snprintf(sum, n, "%ld\n", x+y);
    }
}
void connMain_sum(int connfd) {
    char recvline[MAXLINE];
    char sendline[MAXLINE];
    int n;
    while((n=Readline(connfd,recvline,MAXLINE))>0) {
        //fprintf(stderr,"log: %s\n",recvline);
        addn(sendline,recvline,MAXLINE);
        //fprintf(stderr,"result: %s\n",sendline);
        Writen(connfd, sendline, strlen(sendline));
        //fprintf(stderr,"writen return success\n");
    }
}
void sig_child(int signo)
{
    if(signo==SIGCHLD) {
        int stat;
        pid_t pid;
        while((pid=waitpid(-1, &stat, WNOHANG))>0) {
            fprintf(stderr, "child [%d] terminated.\n", pid);
        }
    } else {
        fprintf(stderr,"caught unexpected signal %d\n",signo);
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
    Mysignal(SIGCHLD, sig_child);
    Listen(listenfd, 32);
    while(1) {
        int connfd = Accept(listenfd, NULL, NULL);
        if(Fork()==0) { // child
            close(listenfd);
            connMain_sum(connfd);
            exit(0);
        }
        //parent
        close(connfd);
    }
}
