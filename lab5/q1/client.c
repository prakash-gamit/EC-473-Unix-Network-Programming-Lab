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
#include <sys/select.h>
#include <netinet/in.h>
#include <errno.h>

/* default server port */
#define PORT 9876

int main(int argc, char *argv[]){

    int connfd; /* socket descriptor */
    struct sockaddr_in server; /* server address struct */
    int len = sizeof(server); /* length of server struct */

    fd_set rset; /* read ser for select */
    int maxfdp1, n;
    char *buff = malloc(1024 * sizeof(char));
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

    FD_ZERO(&rset);
    while(1){
        FD_SET(connfd, &rset);
        FD_SET(fileno(stdin), &rset);
        maxfdp1 = connfd + 1;

        select(maxfdp1, &rset, NULL, NULL, NULL);

        if(FD_ISSET(fileno(stdin), &rset)){
            if(fgets(buff, 1024, stdin) == NULL){
                printf("end-of-file\nexiting...\n");
                break;
            }
            if(send(connfd, buff, strlen(buff)+1, 0) == -1){
                perror("send");
                exit(EXIT_FAILURE);
            }
        }

        if(FD_ISSET(connfd, &rset)){
            if(recv(connfd, buff, 1024, 0) == 0){/* end-of-file received */
                printf("server terminated\nexiting...\n");
                break;
            }
        }
    }
    return 0;
}
