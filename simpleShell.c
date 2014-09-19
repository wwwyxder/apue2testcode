/*************************************************************************
    > File Name: simpleShell.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Fri 05 Sep 2014 04:16:46 PM HKT
 ************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MAXLINE 4096
int main()
{
	char	buf[MAXLINE];
	pid_t pid;
	int status;
	printf("%% ");
	while(fgets(buf, MAXLINE, stdin)!=NULL) {
		if(buf[strlen(buf)-1]=='\n') {
			buf[strlen(buf)-1] = 0;
		}
		if((pid=fork())<0) {
			fprintf(stderr,"fork error");
			exit(126);
		} else if(pid==0) {
			execlp(buf,buf,(char*)0);
			fprintf(stderr,"counld't execute: %s",buf);
			exit(127);
		}
		if((pid=waitpid(pid,&status,0))<0) {
			fprintf(stderr,"wait pid error");
		}
		printf("%% ");
	}
}
