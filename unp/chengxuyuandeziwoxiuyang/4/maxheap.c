#include <stdio.h>
#include <stdlib.h>
unsigned long  maximum = 0;
int main()
{
    unsigned blocksize[]={1024*1024,1024,1};
    int count,i;
    void* block;
    for(i=0;i<3;++i) {
        for(count=1;;++count) {
            block = malloc(maximum+blocksize[i]*count);
            if(block) {
                maximum += blocksize[i]*count;
                free(block);
            } else {
                break;
            }
        }
    }
    free(block);
    printf("maximum malloc size: %u bytes (%u kilo bytes, %u mega bytes)\n",maximum,maximum/1024,maximum/(1024*1024));
    maximum = 0;
    for(i=0;i<3;++i) {
        for(count=1;;++count) {
            block = malloc(blocksize[i]);
            if(block) {
                maximum += blocksize[i];
            } else {
                break;
            }
        }
    }
    free(block);
    printf("total maximum malloc size: %u bytes (%u kilo bytes, %u mega bytes, %f giga bytes)\n",maximum,maximum/1024,maximum/(1024*1024),((maximum/(1024*1024))/1024.0));
    return 0;
}
