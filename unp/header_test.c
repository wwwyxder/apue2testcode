#include "unpheader.h"
int main()
{
    char buf[4096];
    ssize_t n;
    while((n = Readline(STDIN_FILENO, buf, 4096))>0) {
        Writen(STDOUT_FILENO,"[",1);
        Writen(STDOUT_FILENO,buf,n);
        Writen(STDOUT_FILENO,"]\n",2);
    }
    return 0;
}
