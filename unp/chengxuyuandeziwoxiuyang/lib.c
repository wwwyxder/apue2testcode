#include <stdio.h>
#include <unistd.h>
void foobar(int i)
{
    printf("printing from lib.so: %d\n",i);
    while(1) sleep(1);
}
