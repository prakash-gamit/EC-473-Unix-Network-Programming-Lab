/* 
 * File:   que1.c
 * Author: j0k3r
 *
 * Created on August 26, 2012, 3:29 PM
 */

#include "synchronize.h"

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv) {

  int n;
  int fd[2];
  pid_t pid;
  int MAXLINE = 1024;
  char *line = malloc(MAXLINE * sizeof(char));

  INIT();

  if(pipe(fd) < 0){
    perror("pipe error\n");
    exit(1);
  }

  if((pid = fork()) < 0){
    perror("fork error\n");
    exit(1);
  }
  else if(pid > 0){/* parent */
    close(fd[0]);
    printf("child pid = %d\n", pid);
    for(;;){
      printf("parent > ");
      gets(line);
      write(fd[1], line, strlen(line) + 1);

      TELL_CHILD(pid);
      WAIT_FOR_CHILD();

      if(strcmp(line, "STOP") == 0)
        break;
    }
  }
  else{/* child process */
    close(fd[1]);
    for(;;){
      WAIT_FOR_PARENT();
      n = read(fd[0], line, MAXLINE);
      printf("child: %s\n", line);
      TELL_PARENT(getppid());

      if(strcmp(line, "STOP") == 0)
        break;
    }
  }

  return 0;
}

