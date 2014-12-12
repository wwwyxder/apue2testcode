#include <stdio.h>
long global_sym=1;
int _main()
{
    printf("long global_sym, size: %d\n",sizeof(global_sym));
    return 0;
}
