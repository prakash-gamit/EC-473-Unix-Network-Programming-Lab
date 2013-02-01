// =====================================================================================
// 
//       Filename:  exit-status.c
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/01/2012 10:09:24 PM
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
#include <unistd.h>
#include <sys/wait.h>

#include "signame.h"

void report_error(char *msg)
{
  perror(msg);
  exit(1);
}

void exit_status(int status)
{
  //printf("status = %d\n", status);
  if(WIFEXITED(status)){
    printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
  }
  else if(WIFSIGNALED(status)){
    printf("abnormal termination, signal = %s %s\n", get_sig_name(WTERMSIG(status)),
#ifdef WCOREDUMP
        WCOREDUMP(status) ? "(core file generated)" : "");
#else
        "");
#endif
  }
  else if(WIFSTOPPED(status)){
    printf("child stopped, signal = %s\n", get_sig_name(WSTOPSIG(status)));
  }
}

int main()
{
  pid_t pid;
  int status;

  if((pid = fork()) < 0)
    report_error("fork error\n");
  else if(pid == 0)
    exit(10);

  if(wait(&status) != pid)
    report_error("wait error\n");
  exit_status(status);

  if((pid = fork()) < 0)
    report_error("fork error\n");
  else if(pid == 0)
    abort();

  if(wait(&status) != pid)
    report_error("wait error\n");
  exit_status(status);

  if((pid = fork()) < 0)
    report_error("fork error\n");
  else if(pid == 0)
    status /= 0;

  if(wait(&status) != pid)
    report_error("wait error\n");
  exit_status(status);

  exit(0);
}
