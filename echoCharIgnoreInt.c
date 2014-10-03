#include <stdio.h>
#include <unistd.h>
#include <signal.h>
static void sig_int(int signo)
{
	if(signo==SIGINT){
		printf("[..echo..]caught SIGINT.\n");
	}
}
int main()
{
	int c=0;
	struct sigaction act;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	act.sa_handler = sig_int;
	sigaction(SIGINT, &act, NULL);
	while(c!='q') {
		fputc(c, stdout);
		c = fgetc(stdin);
	}
	return 0;
}
