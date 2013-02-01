/* 
 * File:   que1.c
 * Author: j0k3r
 *
 * Created on August 26, 2012, 3:29 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

static volatile sig_atomic_t sigflag; /* set nonzero by sig handler */
static sigset_t newmask, oldmask, zeromask;

static void sig_usr(int signo) /* one signal handler for SIGUSR1 and SIGUSR2 */ {
  sigflag = 1;
}

void INIT(void) {
  /* register signal handler for SIGUSR1 & SIGUSR2 */

  if (signal(SIGUSR1, sig_usr) == SIG_ERR){
      perror("signal(SIGUSR1) error");
      exit(1);
  }

  if (signal(SIGUSR2, sig_usr) == SIG_ERR){
      perror("signal(SIGUSR2) error");
      exit(1);
  }

  sigemptyset(&zeromask);
  sigemptyset(&newmask);

  /* add SIGUSR1 & SIGUSR2 to process signal mask of calling process */
  sigaddset(&newmask, SIGUSR1);
  sigaddset(&newmask, SIGUSR2);
    
  /*
   * Block SIGUSR1 and SIGUSR2, and save current signal mask.
   */
  if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
      perror("SIG_BLOCK error");
      exit(1);
  }
}

void TELL_PARENT(pid_t pid) {
  /* send SIGUSR2 to @pid */
  kill(pid, SIGUSR2); /* tell parent we're done */
}

void WAIT_FOR_PARENT(void) {
  while(sigflag == 0)
    /* sigsuspend bolcks calling process & waits for signal */
    sigsuspend(&zeromask); /* and wait for parent */
  sigflag = 0;

  /*
   * Reset signal mask to original value.
   */
  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
    perror("SIG_SETMASK error");
    exit(1);
  }
}

void TELL_CHILD(pid_t pid) {
  /* send SIGUSR1 to @pid */
  kill(pid, SIGUSR1); /* tell child we're done */
}

void WAIT_FOR_CHILD(void) {
  while (sigflag == 0)
    sigsuspend(&zeromask); /* and wait for child */
  sigflag = 0;

  /*
   * Reset signal mask to original value.
   */
  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
    perror("SIG_SETMASK error");
    exit(1);
  }
}

void fork_error(){
  perror("fork error\n");
  exit(1);
}

/*
 * 
 */

int main(int argc, char** argv) {

  pid_t child1, child2;
  INIT();

  printf("[*] Parent Process:\t\tpid = %d\n", (int)getpid());

  if((child1 = fork()) < 0){ /* fork error */
    fork_error();
  }
  else if(child1 == 0) { /* child process 1 */
    printf("[*] Child Process 1:\t\tpid = %d\n", (int)getpid());

    /* tell parent, pid is printed */
    TELL_PARENT(getppid());

    /* wait for parents signal to continue */
    /* parent will send signal when pid of 2nd child is printed */
    WAIT_FOR_PARENT();

    /* create two grandchildren processes */
    pid_t grandchild1, grandchild2;

    if((grandchild1 = fork()) < 0){
      fork_error();
    }
    else if(grandchild1 == 0) { /* grandchild process 1 */
      printf("[*] Grandchild Process 1:\tpid = %d\n", (int)getpid());

      /* tell child process 1 */
      TELL_PARENT(getppid());
      _exit(0);
    }/* grandchild process 1 */
    
    /* wait for grandchild 1 to print its pid */
    WAIT_FOR_CHILD();

    if((grandchild2 = fork()) < 0){
      fork_error();
    }
    else if(grandchild2 == 0) { /* grandchild process 2 */
      printf("[*] Grandchild Process 2:\tpid = %d\n", (int)getpid());

      /* tell child process 1 */
      TELL_PARENT(getppid());
      _exit(0);
    }/* grandchild process 2 */

    /* pid of both grandchildren is printed */
    /* tell parent to continue */
    TELL_PARENT(getppid());

    /* terminate child 1 */
    _exit(0);

  }/* child process 1 */

  /* wait for child 1 to print its pid */
  WAIT_FOR_CHILD();

  /* fork second child process & print its pid*/

  if((child2 = fork()) < 0){
    fork_error();
  }
  else if(child2 == 0) { /* child process 2 */
    printf("[*] Child Process 2:\t\tpid = %d\n", (int)getpid());

    /* tell parent, pid is printed */
    TELL_PARENT(getppid());

    /* wait for parents signal to continue */
    /* parent will send signal when pid of grandchildren 1 & 2 is printed */
    WAIT_FOR_PARENT();

    pid_t grandchild3, grandchild4;

    if((grandchild3 = fork()) < 0){
      fork_error();
    }
    else if(grandchild3 == 0) { /* grandchild 3 */
      printf("[*] Grandchild Process 3:\tpid = %d\n", (int)getpid());

      /* tell child process 2 */
      TELL_PARENT(getppid());
      _exit(0);
    }/* grandchild 3 */

    /* wait for grandchild 3 to print its pid */
    WAIT_FOR_CHILD();

    if((grandchild4 = fork()) < 0){
      fork_error();
    }
    else if(grandchild4 == 0) { /* grandchild 4 */
      printf("[*] Grandchild Process 4:\tpid = %d\n", (int)getpid());

      /* tell child 2 */
      TELL_PARENT(getppid());
      _exit(0);
    }/* grandchild 4 */

    /* wait for grandchild 2 to print its pid */
    WAIT_FOR_CHILD();

    /* tell parent I'm done */
    TELL_PARENT(getppid());
    /* terminate child 2 */
    _exit(0);

  }/* child process 2 */

  /* wait for child process 2 to print its pid */
  WAIT_FOR_CHILD();

  /* tell child 1 to fork two processes & print their pid */
  TELL_CHILD(child1);

  /* wait for child 1 to finish */
  WAIT_FOR_CHILD();

  /* tell child 2 to fork two processes & print their pid */
  TELL_CHILD(child2);

  /* wait for child2 to finish */
  WAIT_FOR_CHILD();

  printf("done\n");
  return 0;
}

