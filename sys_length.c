#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
    system("getconf LONG_BIT");
    return 0;
}
