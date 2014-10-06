#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <memory.h>
#include <string.h>
#include <arpa/inet.h>
int main()
{
    struct netent *pent;
    size_t index = 0;
    u_int32_t addr;
    if(inet_pton(AF_INET, "127.0.0.1", &addr)==-1) {
        perror("inet_pton error");exit(1);
    }
    addr = ntohl(addr);
    while((pent=getnetent())!=NULL) {
        printf("------------  %d ------------\n",index);
        printf("\tname:\n%s\n",pent->n_name);
        printf("\taddress type:\n%s\n",(AF_INET == pent->n_addrtype)?"ip v4":"no ip v4");
        printf("\tnetwork number:\n%d\n",ntohl(pent->n_net));
        printf("\taliased:\n");
        char **aliases = pent->n_aliases;
        for(int j=0;aliases[j]!=NULL;++j) {
            printf("%s\n",aliases[j]);
        }
        printf("\n");
        ++index;
    }
    printf("[0~%d]\n",index-1);
    return 0;
}
