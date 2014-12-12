#include <stdio.h>
int var_g __attribute__((weak));
int f();
int main()
{
    var_g = 1024;
    f();
    return 0;
}
