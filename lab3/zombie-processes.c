// =====================================================================================
// 
//       Filename:  que3.c
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  08/30/2012 09:48:30 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Prakash Gamit (09211014), <prakashgamit23@gmail.com>
//        Company:  Indian Institute of Technology, Roorkee
// 
// =====================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
  pid_t pid;

  if((pid = fork()) < 0){
    perror("fork error\n");
    exit(1);
  }
  else if(pid == 0){/* 1st child process */
    if((pid = fork()) < 0){
      perror("fork error\n");
      exit(1);
    }
    else if(pid > 0){/* 1st child process */
      printf("1st child process exiting.\n");
      printf("init process in now parent of 2nd child\n");
      _exit(0);
    }

    /* 2nd child process */
    printf("2nd child process continuing.\n");
    sleep(2);
    printf("second child. parent pid = %d\n", getppid());
    printf("2nd child process exiting.\n");
    exit(0);
  }

  /* parent process */
  if(waitpid(pid, NULL, 0) != pid){/* wait for first child */
    perror("waitpid error\n");
    exit(1);
  }
  printf("parent process continuing.\n");
  sleep(3);
  printf("parent process exiting.\n");
  exit(0);
}
