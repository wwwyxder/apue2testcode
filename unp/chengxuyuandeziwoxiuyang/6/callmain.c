#include <stdio.h>
int main(int argc, char* argv[])
{
    if(argc>100) return 0;
    printf("%d\n",argc);
    main(argc+1,argv);
    return 0;
}
