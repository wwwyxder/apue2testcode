#include <stdio.h>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main()
{
    struct sockaddr sa;
    struct in_addr ia;
    struct sockaddr_in sai;
    struct in6_addr i6a;
    struct sockaddr_in6 sai6;
    printf("%d\n",sizeof(sa));
    printf("%d\n",sizeof(ia));
    printf("%d\n",sizeof(sai));
    printf("%d\n",sizeof(i6a));
    printf("%d\n",sizeof(sai6));
    return 0;
}
