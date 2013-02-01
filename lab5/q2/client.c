// =====================================================================================
// 
//       Filename:  client.c
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  Saturday 03 November 2012 10:05:18  IST
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Prakash Gamit (09211014), <prakashgamit23@gmail.com>
//        Organisation:  Indian Institute of Technology, Roorkee
// 
// =====================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>
#include <netinet/in.h>
#include <errno.h>

/* default server port */
#define PORT 9876

/* INFTIM is not defined in poll.h */
#define INFTIM -1

int main(int argc, char *argv[]){

    int connfd; /* socket descriptor */
    struct sockaddr_in server; /* server address struct */
    int len = sizeof(server); /* length of server struct */

    struct pollfd rset[2];
    int ndfs = 2, n;
    char *buff = malloc(1024 * sizeof(char));
    int cli_num;
    /* ****************************************** */

    /* fill server address structure */
    bzero(&server, len);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_aton("127.0.0.1", server.sin_addr.s_addr);
    /* ****************************************** */

    /* create socket */
    if((connfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(EXIT_FAILURE);
    }

    /* connect to server */
    if(connect(connfd, (struct sockaddr *)&server, len) == -1){
        perror("connect");
        exit(EXIT_FAILURE);
    }

    if(recv(connfd, buff, 1024, 0) == -1){
        perror("recv");
        exit(EXIT_FAILURE);
    }
    cli_num = atoi(buff);

    /* set options in pollfd array */
    rset[0].fd = connfd;
    rset[0].events = POLLRDNORM;

    rset[1].fd = fileno(stdin);
    rset[1].events = POLLRDNORM;

    while(1){
        /* print prompt */
        printf("client %d > ", cli_num);

        /* call poll and block */
        poll(rset, ndfs, INFTIM);

        /* if data is ready for reading on @stdin */
        if(rset[1].revents & POLLRDNORM){
            if(fgets(buff, 1024, stdin) == NULL){
                printf("end-of-file\nexiting...\n");
                break;
            }
            if(send(connfd, buff, strlen(buff)+1, 0) == -1){
                perror("send");
                exit(EXIT_FAILURE);
            }
        }

        /* if data is ready for reading on @connfd socket */
        if(rset[0].revents & POLLRDNORM){
            if(recv(connfd, buff, 1024, 0) == 0){/* end-of-file received */
                printf("server terminated\nexiting...\n");
                break;
            }
        }
    }
    return 0;
}
