#include <stdio.h>
int main()
{
    int N = 1000000;
    volatile int k=1;
    while(1) {
        if(k<N) {
            k = k+1;
        } else {
            k = 1;
        }
    }
    return 0;
}
