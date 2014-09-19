#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main()
{
    write(STDOUT_FILENO,"write only one time.",strlen("write only one time."));
    fork();
    return 0;
}
