#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
int main(int argc,char* argv[])
{
    if(argc!=2) {
        fprintf(stderr,"usage: CreatAndChmod <file>\n");
        return 1;
    }
    creat(argv[1],0777);
    chmod(argv[1],0777);
    return 0;
}
