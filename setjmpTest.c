#include <stdio.h>
#include <unistd.h>
#include <setjmp.h>
#include <stdlib.h>
jmp_buf buf;
void f()
{
    longjmp(buf,1);
}
int main()
{
    atexit(f);
    if(setjmp(buf)!=0) {
        printf("gaga return from buf.\n");
    }
    printf("before return.\n");
    return 0;
}
