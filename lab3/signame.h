// =====================================================================================
// 
//       Filename:  signal-name.h
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/02/2012 04:41:52 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Prakash Gamit (09211014), <prakashgamit23@gmail.com>
//        Company:  Indian Institute of Technology, Roorkee
// 
// =====================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

char *get_sig_name(int signo)
{
  if(signo < 1 || signo > SIGRTMAX)
    return "ERROR: NO SIGNAL WITH THIS NUMBER";

  switch(signo)
  {
    case 1: return "SIGHUP";
    case 2: return "SIGINT";
    case 3: return "SIGQUIT";
    case 4: return "SIGILL";
    case 5: return "SIGTRAP";
    case 6: return "SIGABRT";
    case 7: return "SIGBUS";
    case 8: return "SIGFPE";
    case 9: return "SIGKILL";
    case 10: return "SIGUSR1";
    case 11: return "SIGSEGV";
    case 12: return "SIGUSR2";
    case 13: return "SIGPIPE";
    case 14: return "SIGALRM";
    case 15: return "SIGTERM";
    case 16: return "SIGSTKFLT";
    case 17: return "SIGCHLD";
    case 18: return "SIGCONT";
    case 19: return "SIGSTOP";
    case 20: return "SIGTSTP";
    case 21: return "SIGTTIN";
    case 22: return "SIGTTOU";
    case 23: return "SIGURG";
    case 24: return "SIGXCPU";
    case 25: return "SIGXFSZ";
    case 26: return "SIGVTALRM";
    case 27: return "SIGPROF";
    case 28: return "SIGWINCH";
             //SIGPOLL is also 29
             //SIGLOST is also 29
    case 29: return "SIGIO";
    case 30: return "SIGPWR";
    case 31: return "SIGSYS";
    case 32: return "SIGUNUSED";
    default: return "REAL TIME SIGNAL";
  }
}
