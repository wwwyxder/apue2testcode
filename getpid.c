/*************************************************************************
    > File Name: getpid.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Fri 05 Sep 2014 03:12:53 PM HKT
 ************************************************************************/

#include<stdio.h>
#include <unistd.h>
int main()
{
	printf("hello from process ID %d\n",getpid());
	return 0;
}
