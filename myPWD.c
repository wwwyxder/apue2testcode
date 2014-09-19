#include <stdio.h>
#include <unistd.h>
int main()
{
    char buf[4096];
    getcwd(buf,4096);
    printf("%s\n",buf);
    return 0;
}
