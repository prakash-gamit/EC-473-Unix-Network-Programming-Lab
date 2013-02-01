/*
 * =====================================================================================
 *
 *       Filename:  ipaddrconvfun.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/13/2012 12:13:26 PM
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
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
  if(argc < 2 || argv[1] == "-h" || argv[1] == "--help")
  {
    printf("Usage: %s <ip address>\n", argv[0]);
    exit(0);
  }

  char *ip_addr = argv[1];
  struct sockaddr_in something;
  char *some_addr;

  printf("inet_aton() : converting Internet host address from  the  IPv4 numbers-and-dots  notation  into  binary  form (in network byte order)\n\n");

  inet_aton(ip_addr, &something.sin_addr);

  printf("inet_ntoa() : converting the Internet host address given in network byte order, to a string in IPv4 dotted-decimal notation.\n\n");
  
  some_addr = inet_ntoa(something.sin_addr);

  printf("IP address : %s\n", some_addr);

  return 0;
}

