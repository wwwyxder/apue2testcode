/*************************************************************************
    > File Name: read_write.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Fri 05 Sep 2014 02:25:10 PM HKT
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#define BUFFSIZE 4096

int err_sys(char* str)
{
	fprintf(stderr,"%s:%s\n",str,strerror(errno));
	exit(1);
}
int main()
{
	int n;
	char buf[BUFFSIZE];
	while((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
		if(write(STDOUT_FILENO, buf, n) != n) {
			err_sys("write error");
		}
	}
	if(n< 0 ) {
		err_sys("read error");
	}
	exit(0);
}
