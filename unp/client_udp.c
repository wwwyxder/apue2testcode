#include <netinet/in.h>
#include "unpheader.h"
void dg_cli(int fd, struct sockaddr *addr, socklen_t len)
{
    char sendbuf[MAXLINE];
    char recvbuf[MAXLINE];
    while(Fgets(sendbuf, MAXLINE, stdin)!=NULL) {
        Sendto(fd, sendbuf, strlen(sendbuf), 0, addr, len);
        int n = Recvfrom(fd, recvbuf, MAXLINE, 0, NULL, NULL);
        recvbuf[n] = 0;
        Fputs(recvbuf, stdout);
    }
}
int main()
{
    struct sockaddr_in svaddr;
    memset(&svaddr, 0, sizeof(svaddr));
    svaddr.sin_family = AF_INET;
    svaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    svaddr.sin_port = htons(12200);

    int fd = Socket(AF_INET, SOCK_DGRAM, 0);
    int len = sizeof(svaddr);
    dg_cli(fd, (struct sockaddr *)&svaddr, len);
    return 0;
}
