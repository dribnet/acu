
#include "acSocketIO.h"


#ifndef	S_IFSOCK
#error S_IFSOCK not defined
#endif


ssize_t						/* Read "n" bytes from a descriptor. */
readn(int fd, void *vptr, size_t n)
{
  size_t	nleft;
  ssize_t	nread;
  char	*ptr;

  ptr = (char*) vptr;
  nleft = n;

  while (nleft > 0) {
    if ( (nread = read(fd, ptr, nleft)) < 0) {
      if (errno == EINTR)
	nread = 0;		/* and call read() again */
      else
	return(-1);
    } else if (nread == 0)
      break;				/* EOF */

    nleft -= nread;
    ptr   += nread;
  }
  return(n - nleft);		/* return >= 0 */
}
/* end readn */

ssize_t
Readn(int fd, void *ptr, size_t nbytes)
{
  ssize_t		n;

  if ( (n = readn(fd, ptr, nbytes)) < 0)
    {
      printf("readn error\n");
      return 0;
      //exit(0);
    }
  return(n);
}



ssize_t						/* Write "n" bytes to a descriptor. */
writen(int fd, const void *vptr, size_t n)
{
  size_t		nleft;
  ssize_t		nwritten;
  const char	*ptr;

  ptr = (char*)vptr;
  nleft = n;

  int maxfdp1 = fd + 1;
  fd_set rset;
  
  FD_ZERO( &rset );
  FD_SET( fd, &rset );
  timeval tv;
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  
  while (nleft > 0) 
    {
      select( maxfdp1, &rset,NULL, NULL, &tv );
      if ( FD_ISSET( fd, &rset ) )
	{
	  printf("write error: connection %d terminated\n", fd );
	  return (-1);
	}
    
      if ( (nwritten = write(fd, ptr, nleft)) <= 0) 
	{
	  if (errno == EINTR)
	    nwritten = 0;		/* and call write() again */
	  else
	    return(-1);			/* error */
	}

      nleft -= nwritten;
      ptr   += nwritten;
    }
  return(n);
}
/* end writen */

ssize_t
Writen(int fd, void *ptr, size_t nbytes)
{
  if (writen(fd, ptr, nbytes) != nbytes)
    {
      printf("writen error\n");
      // exit(0);
      return 0;
    }
  return 1;
}




/* include sock_ntop */
char* sock_ntop(const struct sockaddr *sa, socklen_t salen)
{
  char		portstr[7];
  static char str[128];		/* Unix domain is largest */

  switch (sa->sa_family) {
  case AF_INET: {
    struct sockaddr_in	*sin = (struct sockaddr_in *) sa;

    if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL)
      return(NULL);
    if (ntohs(sin->sin_port) != 0) {
      snprintf(portstr, sizeof(portstr), ".%d", ntohs(sin->sin_port));
      strcat(str, portstr);
    }
    return(str);
  }
  /* end sock_ntop */

#ifdef	IPV6
  case AF_INET6: {
    struct sockaddr_in6	*sin6 = (struct sockaddr_in6 *) sa;

    if (inet_ntop(AF_INET6, &sin6->sin6_addr, str, sizeof(str)) == NULL)
      return(NULL);
    if (ntohs(sin6->sin6_port) != 0) {
      snprintf(portstr, sizeof(portstr), ".%d", ntohs(sin6->sin6_port));
      strcat(str, portstr);
    }
    return(str);
  }
#endif

#ifdef	AF_UNIX
  case AF_UNIX: {
    struct sockaddr_un	*unp = (struct sockaddr_un *) sa;

    /* OK to have no pathname bound to the socket: happens on
       every connect() unless client calls bind() first. */
    if (unp->sun_path[0] == 0)
      strcpy(str, "(no pathname bound)");
    else
      snprintf(str, sizeof(str), "%s", unp->sun_path);
    return(str);
  }
#endif

#ifdef	HAVE_SOCKADDR_DL_STRUCT
  case AF_LINK: {
    struct sockaddr_dl	*sdl = (struct sockaddr_dl *) sa;

    if (sdl->sdl_nlen > 0)
      snprintf(str, sizeof(str), "%*s",
	       sdl->sdl_nlen, &sdl->sdl_data[0]);
    else
      snprintf(str, sizeof(str), "AF_LINK, index=%d", sdl->sdl_index);
    return(str);
  }
#endif
  default:
    snprintf(str, sizeof(str), "sock_ntop: unknown AF_xxx: %d, len %d",
	     sa->sa_family, salen);
    return(str);
  }
  return (NULL);
}

char * Sock_ntop(const struct sockaddr *sa, socklen_t salen)
{
  char	*ptr;

  if ( (ptr = sock_ntop(sa, salen)) == NULL)
    {
      printf("sock ntop error\n");
      exit(0);
    }
  return(ptr);
}
