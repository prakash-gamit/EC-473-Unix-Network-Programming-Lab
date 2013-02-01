// =====================================================================================
// 
//       Filename:  fifo-file-client.c
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  Monday 17 September 2012 01:40:13  IST
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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <strings.h>

#define SERV_FIFO "/tmp/serverfifo"
#define MAXLINE 1024


int main(int argc, char *argv[])
{
/*
  if(argc != 2){
    printf("usage: %s <filename>\n", argv[0]);
    exit(0);
  }
  */

  int writefifo, readfifo;
  int n, len;
  char fifoname[MAXLINE], buff[MAXLINE];
  pid_t pid;
  char *filename;

  /*
   * create fifoname with PID as part of name
   */
  pid = getpid();
  snprintf(fifoname, sizeof(fifoname), "/tmp/clientfifo.%d", (int)pid);

  /*
   * create private fifo
   */
  if((mkfifo(fifoname, 0777) < 0) && (errno != EEXIST)){
    fprintf(stderr, "cannot create: %s\n", fifoname);
    exit(1);
  }

  /*
   * create message to be sent to the server
   * message format: PID FILENAME
   */
  snprintf(buff, sizeof(buff), "%d ", (int)pid);
  len = strlen(buff);
  filename = buff + len;

  /*
   * get filename from user
   */
   printf("Enter filename: ");
  fgets(filename, MAXLINE - len, stdin);
  len = strlen(buff);

  /*
   * now buff contains our request message
   * and len is length of message
   */

  /*
   * open server fifo for writing
   */
  writefifo = open(SERV_FIFO, O_WRONLY, 0);
  write(writefifo, buff, len);

  /*
   * open private fifo for reading
   */
  readfifo = open(fifoname, O_RDONLY, 0);

  /*
   * read data from private fifo and write it to stdout
   */
  while((n = read(readfifo, buff, MAXLINE)) > 0){
    write(STDOUT_FILENO, buff, n);
    //printf("%s", buff);
  }

  /*
   * close private fifo and then unlink it
   */
  close(readfifo);
  unlink(fifoname);

  return 0;
}
