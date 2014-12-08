#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int getNumber(int n)
{
    if(n<=1) {
        return rand()%16;
    } else {
        return rand()%(int)(powl(16,n));
    }
}
int main()
{
    srand((unsigned int)time(NULL));
    char buf[1024];
    char in[1020];
    int n;
    printf("input n:\n");
    scanf("%d",&n);
    while (1) {
        int a = getNumber(n);
        int b = getNumber(n);
        printf("%X + %X\n",a,b);
        int c;
        scanf("%x",&c);
        if(c==a+b) {
            printf("bingo!\n\n");
        } else {
            printf("%X !\n\n",a+b);
        }
    }
    return 0;
}
