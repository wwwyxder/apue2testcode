#include <stdio.h>
#include <pthread.h>
int pthread_create(pthread_t*, const pthread_attr_t*, void *(*)(void*), void*) __attribute__ ((weak));
int main()
{
    if(pthread_create) {
        printf("pthread_create is linked.\n");
    } else {
        printf("pthread_create unlinked.\n");
    }
    return 0;
}
