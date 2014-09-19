#include <stdio.h>
#include <stdlib.h>
void firstFunc()
{
    printf("first.\n");
}
void secondFunc()
{
    printf("second.\n");
}
int main()
{
    atexit(firstFunc);
    atexit(secondFunc);
    printf("last sentense.\n");
    return 0;
}
