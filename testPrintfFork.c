#include <stdio.h>
#include <unistd.h>
int main()
{
    printf("print only one time.");
    fork();
    printf("\n");
    return 0;
}
