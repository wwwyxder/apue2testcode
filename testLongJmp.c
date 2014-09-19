#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <setjmp.h>
static void f1(int i,int j,int k,int l);
static void f2();
static jmp_buf jmpbuffer;
static int globval;
int main()
{
    int autoval;
    register int regival;
    volatile int volaval;
    static int statval;
    globval = 1;
    autoval = 2;
    regival = 3;
    volaval = 4;
    statval = 5;
    if(setjmp(jmpbuffer) != 0) {
        printf("after longjmp:\n");
        printf(" globval=%d\n autoval=%d\n regival=%d\n volaval=%d\n statval=%d\n",globval,autoval,regival,volaval,statval);
        return 0;
    }
    globval = 95;
    autoval = 96;
    regival = 97;
    volaval = 98;
    statval = 99;
    f1(autoval,regival,volaval,statval);
    return 0;
}
void f1(int i,int j,int k,int l) 
{
    printf(" globval=%d\n autoval=%d\n regival=%d\n volaval=%d\n statval=%d\n",globval,i,j,k,l);
    f2();
}

void f2()
{
    longjmp(jmpbuffer,1);
}
