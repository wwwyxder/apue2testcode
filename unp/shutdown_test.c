#include <arpa/inet.h>
#include <sys/socket.h>
#include "unpheader.h"
int main(int argc, char *argv[])
{
    int clifd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    servaddr.sin_port = htons(12200);
    Connect(clifd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    sleep(1);
    shutdown(clifd,SHUT_RD);
    fprintf(stderr,"after SHUT_RD\n");
    sleep(5);
    fprintf(stderr,"exting...\n");
    return 0;
}
