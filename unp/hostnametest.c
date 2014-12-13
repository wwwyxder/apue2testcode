#include <stdio.h>
#include <netdb.h>
int main(int argc, char *argv[])
{
    if(argc<=1) {
        fprintf(stderr,"usage: %s <name1> ... \n",argv[0]);
        return 1;
    }
    for(int i=1;i<argc;++i) {
        struct hostent* ent = gethostbyname(argv[1]);
        printf("name: %s\n",ent->h_name);
    }
    return 0;
}
