/* include udpservselect01 */
#include <sys/wait.h>
#include	"unpheader.h"

void sig_chld(int signo)
{
    pid_t pid;
    while((pid=waitpid((pid_t)-1, NULL, WNOHANG))>0)
        fprintf(stderr,"child %u exit.\n",pid);//wait any child
}
void tcp_echo(int confd) {
    char readBuffer[MAXLINE];
    int n;
    while(1) {
        n=Read(confd, readBuffer, MAXLINE);
        if(n<0) {
            if(errno == EINTR) {
                continue;
            } else {
                Perror("read error");
            }
        }
        if(n == 0) { //EOF
                Close(confd);
        }
        Writen(confd, readBuffer, n);
    }
}
int
main(int argc, char **argv)
{
	int					listenfd, connfd, udpfd, nready, maxfdp1;
	char				mesg[MAXLINE];
	pid_t				childpid;
	fd_set				rset;
	ssize_t				n;
	socklen_t			len;
	const int			on = 1;
	struct sockaddr_in	cliaddr, servaddr;
	void				sig_chld(int);

		/* 4create listening TCP socket */
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(12200);

	Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	Bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	Listen(listenfd, 128);

		/* 4create UDP socket */
	udpfd = Socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(12200);

	Bind(udpfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
/* end udpservselect01 */

/* include udpservselect02 */
	signal(SIGCHLD, sig_chld);	/* must call waitpid() */

	FD_ZERO(&rset);
	maxfdp1 = myMax(listenfd, udpfd) + 1;
	for ( ; ; ) {
		FD_SET(listenfd, &rset);
		FD_SET(udpfd, &rset);
		if ( (nready = select(maxfdp1, &rset, NULL, NULL, NULL)) < 0) {
			if (errno == EINTR)
				continue;		/* back to for() */
			else
				Perror("select error");
		}

		if (FD_ISSET(listenfd, &rset)) {
			len = sizeof(cliaddr);
			connfd = Accept(listenfd, (struct sockaddr *) &cliaddr, &len);
	
			if ( (childpid = Fork()) == 0) {	/* child process */
				Close(listenfd);	/* close listening socket */
				tcp_echo(connfd);	/* process the request */
				exit(0);
			}
			Close(connfd);			/* parent closes connected socket */
		}

		if (FD_ISSET(udpfd, &rset)) {
			len = sizeof(cliaddr);
			n = Recvfrom(udpfd, mesg, MAXLINE, 0, (struct sockaddr *) &cliaddr, &len);

			Sendto(udpfd, mesg, n, 0, (struct sockaddr *) &cliaddr, len);
		}
	}
}
/* end udpservselect02 */
