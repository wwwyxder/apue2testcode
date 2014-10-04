#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    FILE *file = popen("date","r");
    char buf[4096];
    if(fgets(buf,4096,file)==NULL&&ferror(file)) {
        perror("FILE error");
        exit(1);
    }
    int n = strlen(buf);
    if(n>=1 && buf[n-1]=='\n') buf[n-1] = 0;
    printf("read:[%s]\n",buf);
    return 0;
}
