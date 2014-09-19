#include <stdio.h>
#include <unistd.h>
extern char** environ;
int main()
{
    char** p = environ;
    int N=0;
    while(p[N]!=0) {
        printf("environ[%d]:%s\n",N,p[N]);
        ++N;
    }
    printf("N=%d\n",N);
    return 0;
}
