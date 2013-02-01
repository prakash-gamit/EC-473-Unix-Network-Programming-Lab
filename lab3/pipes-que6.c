// =====================================================================================
// 
//       Filename:  pipes-que6.c
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  08/31/2012 07:17:49 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Prakash Gamit (09211014), <prakashgamit23@gmail.com>
//        Company:  Indian Institute of Technology, Roorkee
// 
// =====================================================================================
#include "synchronize.h"
#include <string.h>

#define MAXLINE 1024

/* 
 * reverse given string
 */
void reverse(char s[])
{
  int i;
  char c;//temp variable
  int len = strlen(s);
  int middle = len/2;

  for(i=0; i<=middle; i++){
    c = s[i];
    s[i] = s[len - 1 - i];
    s[len - 1 - i] = c;
  }
}


int main()
{
  INIT();

  pid_t child;
  char *message = malloc(MAXLINE * sizeof(char));
  int n;

  /* pipes */
  int pipe1[2];
  int pipe2[2];

  if(pipe(pipe1) < 0){
    perror("pipe error\n");
    exit(1);
  }

  if(pipe(pipe2) < 0){
    perror("pipe error\n");
    exit(1);
  }

  if((child = fork()) < 0){
    perror("fork error\n");
    exit(1);
  }
  else if(child == 0){/* child process */
    /* make it a client */
    /* send a string from pipe pipe1 */
    close(pipe1[0]);/* close read end of pipe1 */

    /* receive reversed string from pipe pipe2 */
    close(pipe2[1]);/* close write end of pipe2 */

    while(1){
      printf("********************************************************\n");
      printf(" (child) Enter message: ");
      gets(message);

      write(pipe1[1], message, strlen(message) + 1);
      TELL_PARENT(getppid());

      if(strcmp(message, "STOP") == 0)
        break;

      WAIT_FOR_PARENT();

      n = read(pipe2[0], message, MAXLINE);
      printf(" (child) Parent sent reversed message: %s\n", message);

      TELL_PARENT(getppid());
      WAIT_FOR_PARENT();

      n = read(pipe2[0], message, MAXLINE);
      printf(" (child) Parent sent: %s\n", message);
      printf("********************************************************\n\n");

      if(strcmp(message, "STOP") == 0)
        break;
    }

    printf(" (child) child exiting\n");
    _exit(0);
  }//child 1

  /*
   * parent process
   */
  close(pipe1[1]);
  close(pipe2[0]);

  while(1){
    WAIT_FOR_CHILD();
    n = read(pipe1[0], message, MAXLINE);
    printf("(parent) Child sent: %s\n", message);

    if(strcmp(message, "STOP") == 0)
      break;

    reverse(message);
    write(pipe2[1], message, n);

    TELL_CHILD(child);
    WAIT_FOR_CHILD();

    printf("(parent) Enter message: ");
    gets(message);
    write(pipe2[1], message, strlen(message) + 1);
    TELL_CHILD(child);

    if(strcmp(message, "STOP") == 0)
      break;
  }

  printf("(parent) Parent exiting\n");
  exit(0);
}
