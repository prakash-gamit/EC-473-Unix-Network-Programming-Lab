/* 
 * File:   que1.c
 * Author: j0k3r
 *
 * Created on August 26, 2012, 3:29 PM
 */

#ifndef _SYNCHRONIZE_H_
#define _SYNCHRONIZE_H_

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

#endif
