#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
static void sig_pipe(int signo)
{
    if(signo==SIGPIPE) {
        fprintf(stderr, "SIGPIPE caught.\n");
    }
}
int initserver(int type, const struct sockaddr *addr, socklen_t alen, int qlen)
{
    int err = 0;
    int fd = socket(addr->sa_family, type, 0);
    if(fd<0) return -1;
    if(bind(fd, addr, alen)<0) {
        close(fd);
        return -1;
    }
    if(type == SOCK_STREAM || type == SOCK_SEQPACKET) {
        if(listen(fd, qlen)<0) {
            close(fd);
            return -1;
        }
    }
    return fd;
}
void server(int sockfd)
{
    char buf[4096];
    while(1) {
        errno = 0;
        int clfd = accept(sockfd, NULL, NULL);
        if(clfd < 0) {
            perror("accept error");
            if(errno!=EINTR) {
                exit(1);
            }
        }
        pid_t pid = fork();
        if(pid<0) {
            perror("fork error"); exit(1);
        }
        if(pid==0) { //child
            close(STDIN_FILENO);
            close(STDOUT_FILENO);
            close(STDERR_FILENO);
            if(dup2(clfd, STDOUT_FILENO)<0 || dup2(clfd, STDERR_FILENO)<0) {
                perror("dup2 error");
                exit(1);
            }
            close(clfd);
            execl("/usr/bin/w","w",(char*)0);
        } else { //parent
            int status;
            close(clfd);
            waitpid(pid, &status, 0);
        }
    }
}
int main()
{
//    signal(SIGPIPE, sig_pipe);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    u_int32_t tmp_addr;
    inet_pton(AF_INET, "127.0.0.1", &tmp_addr);
    addr.sin_addr.s_addr = tmp_addr;//htonl(tmp_addr);
    addr.sin_port = htons(12200);
    memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));
    int fd = initserver(SOCK_STREAM, (struct sockaddr*)&addr, sizeof(struct sockaddr_in),128);
    if(fd<0) {
        perror("initial server error.\n");
        exit(1);
    }
    printf("initial server success.\n");
    server(fd);
    return 0;
}
