#include <stdio.h>
#include <unistd.h>
extern char** environ;
static void f();
int main(int argc,char* argv[])
{
    f();
    return 0;
}
void f()
{
    char** f = environ;
    int cnt = 0;
    while(f!=0) {
        printf("[%d]:%s",cnt,*f);
        ++cnt;
    }
    return;
}
