#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
int mySystem(const char* cmd)
{
	pid_t pid;
	int status = 0;
	if((pid=fork())<0) {
		perror("fork error in mySystem");
		exit(1);
	} else if(pid == 0) { //child
		execl("/bin/sh","sh","-c",cmd,(char*)0);
		_exit(127);
	} else { //parent
		while(waitpid(pid, &status, 0)<0) {
			if(errno==EINTR) continue;
			status = -1;
			break;
		}
	}
	return status;
}
static void perr_exit(const char* msg)
{
	perror(msg);
	exit(1);
}
int mySystem2(const char* cmd)
{
	pid_t pid;
	int status = 0;
	struct sigaction ignore, saveintr, savequit;
	sigset_t chldmask, savemask;
	ignore.sa_handler = SIG_IGN;
	sigemptyset(&ignore.sa_mask);
	ignore.sa_flags = 0;
	if(sigaction(SIGINT, &ignore, &saveintr)<0)
		perr_exit("sigaction SIGINT error");
	if(sigaction(SIGQUIT, &ignore, &savequit)<0)
		perr_exit("sigaction SIGQUIT error");
	sigemptyset(&chldmask);
	sigaddset(&chldmask, SIGCHLD);
	if(sigprocmask(SIG_BLOCK, &chldmask, &savemask)<0)
		perr_exit("sigprocmask error");
	if((pid=fork())<0) {
		perror("fork error in mySystem");
		exit(1);
	} else if(pid == 0) { //child
		sigaction(SIGINT, &saveintr, NULL);
		sigaction(SIGQUIT, &savequit, NULL);
		sigprocmask(SIG_BLOCK, &savemask, NULL);
		execl("/bin/sh","sh","-c",cmd,(char*)0);
		_exit(127);
	} else { //parent
		while(waitpid(pid, &status, 0)<0) {
			if(errno==EINTR) continue;
			status = -1;
			break;
		}
	}
	if(sigaction(SIGINT, &saveintr, NULL)<0)
		perr_exit("reset sigaction SIGINT error");
	if(sigaction(SIGQUIT, &savequit, NULL)<0)
		perr_exit("reset sigaction SIGQUIT error");
	if(sigprocmask(SIG_SETMASK, &chldmask, &savemask)<0)
		perr_exit("reset sigprocmask error");
	return status;
}
static void sig_int(int signo) 
{
	printf("caught INT.\n");
}
static void sig_chld(int signo)
{
	printf("caught CHLD.\n");
}
int main()
{
	signal(SIGINT, sig_int);
	signal(SIGCHLD, sig_chld);
	system("./echoCharIgnoreInt");
    printf("return from system.\n");
	return 0;
}
