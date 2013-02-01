// =====================================================================================
// 
//       Filename:  fifo-file-server.c
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  Monday 10 September 2012 03:38:31  IST
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
#include <errno.h>
#include <fcntl.h>

#define SERV_FIFO "/tmp/serverfifo"
#define MAXLINE 1024

int main(){

  int readfifo, writefifo, dummyfifo, fd;
  int n;
  char buff[MAXLINE], fifoname[MAXLINE], *filename;
  pid_t pid;

  if(mkfifo(SERV_FIFO, 0777) < 0 && errno != EEXIST){
    printf("cannot create %s\n", SERV_FIFO);
    exit(-1);
  }

  /*
   * open server fifo for reading
   */
   printf("starting server process:\n");
  readfifo = open(SERV_FIFO, O_RDONLY, 0);
  /*
   * open server fifo for writing
   * server will never write to this fifo
   */
  dummyfifo = open(SERV_FIFO, O_WRONLY, 0);

  /*
   * all the clients will use their fifonames as /tmp/clientfifo.$pid
   * where $pid is pid of client process
   */

  /*
   * read fifoname(i.e pid of client process)
   */
  while((n = read(readfifo, buff, MAXLINE)) > 0){
     if (buff[n-1] == '\n')
			n--;			/* delete newline from readline() */
	buff[n] = '\0';
    /*
     * request will be of the form
     * pid filename
     * pid => pid of the requesting client
     * filename => file requested by client
     */
    if((filename = strchr(buff, ' ')) == NULL){
      fprintf(stderr, "bogus request: %s\n", buff);
      continue;
    }
    
    printf("%s\n", buff);

    /*
     * 'filename' pointer is currently pointing to ' ' in request
     * increment it to point to first character of filename in request
     */
    *filename++ = 0;

    /*
     * store clients fifoname in 'fifoname'
     */
    snprintf(fifoname, sizeof(fifoname),"/tmp/clientfifo.%d", atoi(buff));

    /*
     * open clients fifo for writing
     */
    if((writefifo = open(fifoname, O_WRONLY, 0)) < 0){
     printf("cannot open: %s", fifoname);
      continue;
    }

    /*
     * open file requested by client for reading
     */
    if((fd = open(filename, O_RDONLY)) < 0){
      sprintf(buff, "cannot open, %s\n", filename);
      write(writefifo, buff, MAXLINE);
    }
    else {
      while((n = read(fd, buff, MAXLINE)) > 0){
        write(writefifo, buff, n);
      }
      close(fd);
    }
    close(writefifo);
  }

  exit(0);
}
