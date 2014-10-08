#include <stdio.h>
int main()
{
    short n = 0x0201;
    char* p = (char*)&n;
    if(*p==1) {
        printf("Little Endian\n");
    } else if(*p==2) {
        printf("Big Endian\n");
    } else {
        printf("Who Knows?\n");
    }
    return 0;
}
