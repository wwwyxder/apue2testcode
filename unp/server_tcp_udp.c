#include <sys/wait.h>
#include "unpheader.h"

void sig_chld(int signo)
{
    pid_t pid;
    while((pid=waitpid((pid_t)-1, NULL, WNOHANG))>0)
        fprintf(stderr,"child %u exit.\n",pid);//wait any child
}
void tcp_echo(int confd) {
    char readBuffer[MAXLINE];
    int n;
    while(1) {
        n=Read(confd, readBuffer, MAXLINE);
        if(n<0) {
            if(errno == EINTR) {
                continue;
            } else {
                Perror("read error");
            }
        }
        if(n == 0) { //EOF
                Close(confd);
        }
        Writen(confd, readBuffer, n);
    }
}
int main()
{
    struct sigaction act, oact;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_handler = &sig_chld;
    sigaction(SIGCHLD, &act, &oact);
    struct sockaddr_in svaddr;
    memset(&svaddr, 0, sizeof(svaddr));
    svaddr.sin_family = AF_INET;
    svaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    svaddr.sin_port = htons(12200);
    struct sockaddr_in svaddr_2;
    memcpy(&svaddr_2,&svaddr,sizeof(svaddr));//debug
    int listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    int udpfd = Socket(AF_INET, SOCK_DGRAM, 0);
    int maxfdp1 = (int)myMax(listenfd, udpfd)+1;
    int on = 1;
    Setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
    Bind(listenfd, (struct sockaddr*)&svaddr,sizeof(svaddr));
    Listen(listenfd,128);
    if(memcmp(&svaddr,&svaddr_2,sizeof(svaddr))!=0) {fprintf(stderr,"addr changed.\n");return 1;}
    Bind(udpfd, (struct sockaddr*)&svaddr, sizeof(svaddr));
    fd_set rset;
    while(1) {
        fprintf(stderr,"debug: listenfd: %d\t udpfd: %d\n",listenfd, udpfd);
        FD_ZERO(&rset);
        FD_SET(listenfd, &rset);
        FD_SET(udpfd, &rset);
        int nready=Select(maxfdp1, &rset, NULL, NULL, NULL);
        if(1) {
            fprintf(stderr,"nready:%d\nlistenfd:%d\nudpfd:%d\n",nready,FD_ISSET(listenfd,&rset),FD_ISSET(udpfd,&rset));
        }
        if(nready<0) {
            if(errno==EINTR) {
                continue;
            } else {
                Perror("select error");
            }
        }
        if(FD_ISSET(listenfd, &rset)) {
            int confd = Accept(listenfd, NULL, NULL);
            pid_t childpid = Fork();
            if(childpid==0) {
                Close(listenfd);
                tcp_echo(confd);
                exit(0);
            }
            Close(confd);
        }
        if(FD_ISSET(udpfd, &rset)) {
            struct sockaddr_in cliaddr;
            int len=sizeof(cliaddr);
            char buf[MAXLINE];
            fprintf(stderr,"udp listener ready.\n");
            int n = Recvfrom(udpfd, buf, MAXLINE, 0, (struct sockaddr*)&cliaddr, &len);
            Sendto(udpfd, buf, n, 0, (struct sockaddr*)&cliaddr, len);
        }
    }
}
