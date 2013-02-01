// =====================================================================================
// 
//       Filename:  server.c
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  Saturday 03 November 2012 09:36:16  IST
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
#include <strings.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <poll.h>
#include <sys/stropts.h>

/* default server port */
#define PORT 9876

/* server backlog */
#define BACKLOG 5

/* INFTIM is not defined in poll.h */
#define INFTIM -1

int main(int argc, char *argv[]){

    int listenfd, /* listening socket */
        connfd[3]; /* connected socket */

    struct sockaddr_in server, /* server address structure */
                       client; /* client address structure */

    int len = sizeof(server);
    int nfds = 3, n;
    struct pollfd rset[3];
    char *buff = malloc(1024 * sizeof(char));
    /* ************************************************ */

    /* fill server address structure */
    bzero(&server, len);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    /* create socket */
    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(EXIT_FAILURE);
    }

    /* set SO_REUSEADDR */
    int ON = 1;
    if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, 
                (void *)&ON, sizeof(int)) == -1){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    /* bind it to a wildcard address and port @PORT */
    if(bind(listenfd, (struct sockaddr *)&server, len) == -1){
        perror("bind");
        exit(EXIT_FAILURE);
    }

    /* start listening */
    if(listen(listenfd, BACKLOG) == -1){
        perror("listen");
        exit(EXIT_FAILURE);
    }

    int i;
    /* accept 3 connection */
    for(i = 0; i < 3; i++){
        if((connfd[i] = accept(listenfd, (struct sockaddr *)&client, &len)) == -1){
            perror("accept");
            exit(EXIT_FAILURE);
        }

        sprintf(buff, "%d", i);
        if(send(connfd[i], buff, strlen(buff), 0) == -1){
            perror("send");
            exit(EXIT_FAILURE);
        }
    }

    for(i = 0; i < 3; i++){
        rset[i].fd = connfd[i];
        rset[i].events = POLLRDNORM;
    }

    while(1){
        /* call poll
         * it will block
         */
        poll(rset, nfds, INFTIM);

        for(i = 0; i < 3; i++){
            if(rset[i].revents & POLLRDNORM){
                if((n = recv(connfd[i], buff, 1024, 0)) == -1){/* error */
                    perror("recv");
                    exit(EXIT_FAILURE);
                } else if(n == 0){/* end of file */
                    exit(EXIT_SUCCESS);
                }

                printf("data received from client %d: %s\n", i, buff);
            }
        }
    }

    return 0;
}
