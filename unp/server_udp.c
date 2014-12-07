#include <netinet/in.h>
#include "unpheader.h"
void dg_echo(int svfd, struct sockaddr* cliaddr,int addrlen)
{
    char buf[MAXLINE];
    while(1) {
        int len=addrlen;
        int n = Recvfrom(svfd, buf, MAXLINE, 0, cliaddr, &len);
        Sendto(svfd,buf,n,0,cliaddr,len);
    }
}
int main()
{
    struct sockaddr_in addr;
    struct sockaddr_in cliaddr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(12200);
    int svfd = Socket(AF_INET, SOCK_DGRAM, 0);
    Bind(svfd, (struct sockaddr*)&addr,sizeof(addr));
    dg_echo(svfd,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
    return 0;
}
