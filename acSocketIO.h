
#include        <sys/types.h>   /* basic system data types */
#include        <sys/socket.h>  /* basic socket definitions */
#include        <sys/time.h>    /* timeval{} for select() */
#include        <time.h>                /* timespec{} for pselect() */
#include        <netinet/in.h>  /* sockaddr_in{} and other Internet defns */
#include        <arpa/inet.h>   /* inet(3) functions */
#include        <errno.h>
#include        <fcntl.h>               /* for nonblocking */
#include        <netdb.h>
#include        <signal.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        <string.h>
#include        <sys/stat.h>    /* for S_xxx file mode constants */
#include        <sys/uio.h>             /* for iovec{} and readv/writev */
#include        <unistd.h>
#include        <sys/wait.h>
#include        <sys/un.h>              /* for Unix domain sockets */
#include        <pthread.h>


#define socklen_t int

char* sock_ntop(const struct sockaddr *sa, socklen_t salen);
char* Sock_ntop(const struct sockaddr *sa, socklen_t salen);


ssize_t readn(int fd, void *vptr, size_t n);
ssize_t Readn(int fd, void *ptr, size_t nbytes);

ssize_t writen(int fd, const void *vptr, size_t n);
ssize_t Writen(int fd, void *ptr, size_t nbytes);
