// =====================================================================================
// 
//       Filename:  race-condition2.c
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/02/2012 12:00:02 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Prakash Gamit (09211014), <prakashgamit23@gmail.com>
//        Company:  Indian Institute of Technology, Roorkee
// 
// =====================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "synchronize.h"

static void charatatime(char *);

int main()
{
  INIT();
  pid_t pid;

  if((pid = fork()) < 0){
    perror("fork error\n");
    exit(1);
  }
  else if(pid == 0){
    charatatime("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000\n");
    TELL_PARENT(getppid());
  }
  else{
    WAIT_FOR_CHILD();
    charatatime("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111\n");
  }

  exit(0);
}

static void charatatime(char *str)
{
  char *ptr;
  int c;

  setbuf(stdout, NULL);
  for(ptr = str; (c = *ptr++) != 0;)
    putc(c,stdout);
}
