/*
 * =====================================================================================
 *
 *       Filename:  que7.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/12/2012 05:11:46 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Prakash Gamit (), prakashgamit23@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main()
{
  int retval;
  struct in_addr addrptr;
  memset(&addrptr, '\0', sizeof(addrptr));
  retval = inet_addr("127.0.0.1", &addrptr);

  printf("retval = %d\n",retval);

  return 0;
}
