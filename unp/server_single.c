#include <netinet/in.h>
#include "unpheader.h"
void print_fdset(fd_set s)
{
    printf("{");
    int fisrt = 1;
    for(int i=0;i<FD_SETSIZE;++i) {
        if(FD_ISSET(i,&s)) {
            if(!fisrt)
                printf(",%d",i);
            else
                printf("%d",i);
            fisrt = 0;
        }
    }
    printf("}\n");
}
int main()
{
    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(12200);
    int listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt))<0) Perror("setsockopt error");
    Bind(listenfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    Listen(listenfd, 20);
    int connfds[FD_SETSIZE];
    int end_connfds = 0;
    int maxfd = listenfd;
    fd_set fdset_conn;
    for(int i=0;i<FD_SETSIZE;++i) connfds[i] = -1;
    FD_ZERO(&fdset_conn);
    FD_SET(listenfd, &fdset_conn);
    while(1) {
        fd_set rset = fdset_conn;
        int ns = Select(maxfd+1, &rset, NULL, NULL, NULL);
        //fprintf(stderr,"ns:%d ",ns);print_fdset(rset); kill(getpid(),SIGTSTP);
        if(FD_ISSET(listenfd, &rset)) {
          //          fprintf(stderr,"accept "); kill(getpid(),SIGTSTP);
            int newconnfd = Accept(listenfd, NULL, NULL);
            int index;
            for(index=0;index<FD_SETSIZE;++index) {
                if(connfds[index]==-1) {
                    connfds[index] = newconnfd;
                    end_connfds = myMax(index+1,end_connfds);
                    break;
                }
            }
            if(index==FD_SETSIZE)
                Perror("too many connections");
            FD_SET(newconnfd, &fdset_conn);
            maxfd = myMax(newconnfd, maxfd);
            --ns;
        }
        for(int i=0;i<end_connfds && ns>0;++i) {
            if(connfds[i]!=-1 && FD_ISSET(connfds[i],&rset)) {
                int n;
                int buf[MAXLINE];
                if((n=Read(connfds[i],buf,MAXLINE))>=0) {
                    if(n==0) { //client send EOF
                        close(connfds[i]);
                        FD_CLR(connfds[i],&fdset_conn);
                        connfds[i] = -1;
                    } else {
                        Writen(connfds[i],buf,n);
                    }
                }
                --ns;
            }
        }
    }
    return 0;
}
