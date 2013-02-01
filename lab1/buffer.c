/*
 * =====================================================================================
 *
 *       Filename:  buffer.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/13/2012 02:11:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Prakash Gamit (), prakashgamit23@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

int main()
{
  int n;
  unsigned int m = sizeof(n);
  int sd = socket(AF_INET, SOCK_STREAM, 0);
  getsockopt(sd, SOL_SOCKET, SO_RCVBUF, (void *)&n, &m);
  //now n will have buffer size

  printf("%d\n", n);

  n = 20000;
  m = sizeof(n);
  setsockopt(sd, SOL_SOCKET, SO_RCVBUF,(void *) &n,(socklen_t) &m);

  m = sizeof(n);
  getsockopt(sd, SOL_SOCKET, SO_RCVBUF, &n, &m);
  printf("%d\n", n);

  return 0;
}
