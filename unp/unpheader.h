#ifndef __UNPHEADER_H__
#define __UNPHEADER_H__
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <poll.h>
#include <netinet/in.h> //for freeBSD
void Perror(const char *s)
{
    perror(s);
    exit(1);
}
char* Fgets(char* ptr, int n, FILE *stream)
{
    char *rptr = fgets(ptr,n,stream);
    if(rptr==NULL && ferror(stream)) 
        Perror("fgets error");
    return rptr;
}
int Fputs(char *ptr, FILE *stream)
{
    int r = fputs(ptr,stream);
    if(r==EOF)
        Perror("fputs error");
    return r;
}
int Socket(int domain, int type, int protocol)
{
    int fd = socket(domain, type, protocol);
    if(-1 == fd) {
        Perror("socket error");
    }
    return fd;
}
int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    if(bind(sockfd, addr, addrlen)==-1 ) {
        Perror("bind error");
    }
    return 0;
}
int Listen(int sockfd, int backlog)
{
    if(listen(sockfd, backlog) == -1) {
        Perror("listen error");
    }
    return 0;
}
int Accept(int sockfd, struct sockaddr *addr, socklen_t *socklen)
{
    int confd;
    while((confd = accept(sockfd, addr, socklen)) == -1) {
        if(errno==EINTR || errno==ECONNABORTED)
            Perror("accept error");
    }
    return confd;
}
int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    if(connect(sockfd, addr, addrlen)==-1)
        Perror("connect error");
    return 0;
}
ssize_t writen(int fd, const void *buf, size_t count)
{
    size_t n, left=count;
    const char *p = buf;
    while(left>0) {
        n = write(fd, p, left);
        if(n <= 0) {
            if(n<0 && EINTR == errno)
                continue;
            return -1; // if we can't write (count) bytes, it would be an error for the caller.
        } else {
            left -= n;
            p += n;
        }
    }
    return count;
}
ssize_t Writen(int fd, const void *buf, size_t count)
{
    if(writen(fd, buf, count)!=count) {
        Perror("writen error");
    }
    return count;
}
ssize_t readn(int fd, void *buf, size_t count)
{
    size_t n, left = count;
    char *p = buf;
    while(left > 0) {
        n = read(fd, p, left);
        if(0 == n) {
            break;//EOF
        } else if(n < 0) { //error or interrupted
            if(EINTR == errno) {
                continue;
            } else {
                return -1;//something error we can't deal
            }
        } else { //write n bytes
            left -= n;
            p += n;
        }
    }
    return count-left;
}
ssize_t Readn(int fd, void *buf, size_t count)
{
    ssize_t n = readn(fd, buf, count);
    if(-1 == n) 
        Perror("readn error");
    return n;
}
ssize_t Read(int fd, void *buf, size_t count)
{
    ssize_t n = read(fd,buf,count);
    if(n==-1)
        Perror("read error");
    return n;
}

/*
 *readline() buffers and states and helper functions
 *read_cnt : the number of chars in buffer
 *read_ptr : pointer to the char which will be read when call my_read() next time
 *read_buf : the buffer
 *my_read(), special version of read() to read from buffer, only read one char at most
 */
#ifndef MAXLINE
#define MAXLINE 4096
#endif
static ssize_t read_cnt = 0;
static char *read_ptr = NULL;
static char read_buf[MAXLINE];

static ssize_t my_read(int fd, char *c)
{
    while(read_cnt<=0) {
        read_cnt = read(fd, read_buf, MAXLINE);
        if(read_cnt<0) {
            if(EINTR == errno)
                continue;
            else
                return -1;
        } else if(0 == read_cnt) {
            return 0;
        } else {
            read_ptr = read_buf;
            break;
        }
    }
    *c = *read_ptr++;
    --read_cnt;
    return 1;
}
/*
 * readlinebuf()
 * store the remaining buffer data's addr to vptrptr
 * return read_cnt (>0 means still data in buffer)
 */
ssize_t getlinebuf(char **vptrptr)
{
    if(read_cnt>0)
        *vptrptr = read_ptr;
    return read_cnt;
}
/*readline:
 *read a line of string, at most maxlen-1 chars
 *keep the last '\n' char if exist
 *in success, return the number of chars reads, including '\n', in other word, strlen(buf).
 *if error, return -1
 */
ssize_t readline(int fd, void *buf, size_t maxlen)
{
    char *p = buf;
    size_t i;
    for(i=1;i<maxlen;++i) {
        char c;
        int n = my_read(fd, &c);
        if(1==n) {
            *p++ = c;
            if('\n' == c)
                break;
        } else if(0 == n) {
            *p = 0;
            return i-1;
        } else {
            return -1;
        }
    }
    *p = 0;
    return i;
}
ssize_t Readline(int fd, void *buf, size_t maxlen)
{
    ssize_t n = readline(fd, buf, maxlen);
    if(-1 == n)
        Perror("readline error");
    return n;
}
pid_t Fork()
{
    pid_t pid;
    if( (pid=fork()) < 0) {
        Perror("fork error");
    }
    return pid;
}
typedef void Sigfunc(int);
Sigfunc *mysignal(int signo, Sigfunc* sigfunc)
{
    struct sigaction act, oact;
    act.sa_handler = sigfunc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if(signo==SIGALRM) {
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
#endif
    } else {
#ifdef SA_RESTART
        act.sa_flags |= SA_RESTART;
#endif
    }
    if(sigaction(signo, &act, &oact)<0)
        return SIG_ERR;
    return oact.sa_handler;
}
Sigfunc *Mysignal(int signo, Sigfunc *sigfunc)
{
    Sigfunc *f = mysignal(signo, sigfunc);
    if(f==SIG_ERR)
        Perror("sigaction error");
    return f;
}
int Close(int fd) {
    int r = close(fd);
    if(r==-1)
        Perror("close error");
    return r;
}
int Select(int nfds, fd_set* read_set, fd_set* write_set, fd_set* except_set, struct timeval *val)
{
    int r;
    while((r=select(nfds,read_set,write_set,except_set,val))==-1) {
        if(errno==EINTR)
            continue;
        Perror("select() error");
    }
    return r;
}
int Poll(struct pollfd* fds, nfds_t size, int timeout)
{
    int nready;
    while((nready=poll(fds,size,timeout))<0) {
        if(errno == EINTR) 
            continue;
        break;
    }
    return nready;
}
ssize_t Recvfrom(int fd, void* buf, size_t buflen, int flags, struct sockaddr* addr, socklen_t *addrlen)
{
    int n;
    while((n=recvfrom(fd,buf,buflen,flags,addr,addrlen))==-1) {
        if(errno == EINTR) continue;
        Perror("recvfrom error");
        break;
    }
    return n;
}
ssize_t Sendto(int fd, const void *buf, size_t buflen, int flags, const struct sockaddr *dstaddr, socklen_t addrlen)
{
    int n;
    while((n=sendto(fd,buf,buflen,flags,dstaddr,addrlen))==-1) {
        if(errno==EINTR) continue;
        Perror("sendto error");
        break;
    }
    return n;
}
long myMax(long x, long y)
{
    return x>=y?x:y;
}
#endif
