// =====================================================================================
// 
//       Filename:  que2.c
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  08/30/2012 10:06:16 PM
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


int main(int argc, char *argv[], char *envp[])
{
  pid_t pid;
  char *cmd = "./helloworld";

  if((pid = fork()) < 0){
    perror("fork error\n");
    exit(1);
  }
  else if(pid == 0){/* child process */
    printf("in child process\nreplacing image using execv\n");
    execv(cmd, NULL);

    //never reach code below
    printf("executed command\n");
    _exit(0);
  }

  /* parent process */
  printf("in parent process\n");
  sleep(2);
  printf("parent process terminated\n");

  return 0;
}
