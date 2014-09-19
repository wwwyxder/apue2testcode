#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>
//typedef void (SigHdl*)(int signo);
void sig_int(int signo);
int main()
{
	char buf[4096];
	pid_t pid;
	int status;
	if(SIG_ERR == signal(SIGINT,sig_int)) {
		perror("signal error");
		return 1;
	}
	printf("%%");
	while(fgets(buf,4096,stdin)!=NULL) {
		if(buf[strlen(buf)-1]=='\n') {
			buf[strlen(buf)-1] = 0;
		}
		pid = fork();
		if(pid<0) {
			perror("fork error");
			return 1;
		} else if(pid==0) {//child
			execlp(buf,buf,(char*)0);
			perror("couldn't execute");
			return 1;
		} else {
			if(pid = waitpid(pid,&status,0)<0) {
				perror("waite pid error");
				return 1;
			}
			printf("%%");
		}
	}
	return 0;
}
void sig_int(int signo)
{
	printf("catched signal [%d].\n%%",signo);
	fflush(stdout);
}
