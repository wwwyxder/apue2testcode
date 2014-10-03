#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
static void sig_quit(int signo);
int main()
{
	sigset_t newset, oldset, pendmask;
	if(signal(SIGQUIT,sig_quit)) {
		perror("signal(SIGQUIT) error");
		exit(1);
	}
	sigemptyset(&newset);
	sigaddset(&newset,SIGQUIT);
	if(sigprocmask(SIG_BLOCK, &newset, &oldset)) {
		perror("sigprocmask SIG_BLOCK error");
		return 1;
	}
	printf("SIGQUIT blocked.\nsleep starting.\n");
	sleep(5);
	printf("wake up.\n");
	
	if(sigpending(&pendmask) < 0) {
		perror("sigpending error");
		exit(1);
	}
	if(sigismember(&pendmask,SIGQUIT)) {
		printf("\nSIGQUIT pending.\n");
	}

	if(sigprocmask(SIG_SETMASK, &oldset, NULL)) {
		perror("sigprocmask SIG_SETMASK error");
		exit(1);
	}
	//signal will be deliveried here
	//"caught SIGQUIT." will print before "SIGQUIT unblocked."
	printf("SIGQUIT unblocked.\n");
	
	printf("sleep starting again.\n");
	sleep(5);
	printf("wake up again.\n");
}
static void sig_quit(int signo)
{
	printf("caught SIGQUIT.\n");
	if(signal(SIGQUIT,SIG_DFL)==SIG_ERR) {
		perror("reset signal(SIGQUIT) error.\n");
		exit(1);
	}
}
