#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
int main(int argc,char* argv[])
{
    umask(0);
    if(argc!=2) {
        fprintf(stderr,"usage:testCreatFile <file name>.\n");
        return 1;
    }
    creat(argv[1],0777);
    return 0;
}
