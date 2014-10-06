#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
int main()
{
    u_int32_t i32;
    while(scanf("%d",&i32)==1) {
        printf("host:0x%08x\n net:0x%08x\n",i32,htonl(i32));
    }
    return 0;
}
