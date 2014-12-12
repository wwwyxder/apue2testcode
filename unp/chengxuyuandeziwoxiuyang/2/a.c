#include <stdio.h>
char global_sym;
int main()
{
    printf("char global_sym, size: %d\n",sizeof(global_sym));
    return 0;
}
