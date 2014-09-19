#include <stdio.h>
#include <sys/stat.h>
int main(int argc,char* argv[])
{
    if(argc!=2) {
        fprintf(stderr,"usage: ls <file>\n");
        return 1;
    }
    struct stat s;
    stat(argv[1],&s);
    return 0;
}
