#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
int main()
{
    struct servent *pserv;
    int index = 1;
    while((pserv=getservent())!=NULL) {
        printf("\t\t---- %d ----\n",index);
        printf("\tname\n%s\n",pserv->s_name);
        printf("\tport\n%d\n",pserv->s_port);
        printf("\tprotocol\n%s\n",pserv->s_proto);
        char **names = pserv->s_aliases;
        printf("\talternate names\n");
        for(int i=0;names[i]!=NULL;++i) {
            printf("%s\n",names[i]);
        }
        ++index;
    }
    return 0;
}
