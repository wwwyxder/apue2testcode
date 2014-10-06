#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <memory.h>
#include <arpa/inet.h>
int main()
{
    struct hostent h;
    size_t size = sizeof(h);
    struct hostent *ph;
    while((ph=gethostent())!=NULL) {
        memcpy(&h,gethostent(),size);
        printf("------------- host names------------\n");
        printf("\t%s\t(name)\n",h.h_name);
        char **list = h.h_aliases;
        for(int i=0;list[i]!=0;++i) {
            printf("\t%s\n",list[i]);
        }
        printf("------------- host addr------------\n");
        list = h.h_addr_list;
        for(int i=0;list[i]!=0;++i) {
            char buf[64];
            inet_ntop(AF_INET, list[i], buf, 64);
            printf("\t%s\n",buf);
        }
        printf("\n\n");
    }
    return 0;
}
