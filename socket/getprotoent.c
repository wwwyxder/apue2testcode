#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
int main()
{
    struct protoent *pproto;
    int index = 1;
    while((pproto=getprotoent())!=NULL) {
        printf("\t\t---- %d ----\n",index);
        printf("\tname\n%s\n",pproto->p_name);
        char **names = pproto->p_aliases;
        printf("\talternate protocol names\n");
        for(int i=0;names[i]!=NULL;++i) {
            printf("%s\n",names[i]);
        }
        printf("\ttype\n%d\n",pproto->p_proto);
        //printf("\ttype\n%s\n",(pproto->p_proto==AF_INET)?"IPv4":"Not IPv4");
        ++index;
    }
}
