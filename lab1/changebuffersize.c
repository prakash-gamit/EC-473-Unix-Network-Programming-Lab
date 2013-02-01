#include<stdio.h>

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <assert.h>

int main()
{
	int fd=socket(AF_INET,SOCK_STREAM,0);
	int snd_buf,recv_buf;
	int changed_value;
	unsigned int m=sizeof(snd_buf);
	unsigned int n=sizeof(recv_buf);	
	getsockopt(fd,SOL_SOCKET,SO_SNDBUF,(void *)&snd_buf,&m);
	getsockopt(fd,SOL_SOCKET,SO_RCVBUF,(void *)&recv_buf,&n);	
	printf("\nThe default value for send buffer is %d\n",snd_buf);
	printf("\nThe default value for receive buffer is %d\n",recv_buf);	
	printf("\nEnter the size to be set:");
	scanf("%d",&changed_value);
	printf("\nChanging the value of receive buffer to %d\n",changed_value);
	int t=sizeof(int);	
	setsockopt(fd,SOL_SOCKET,SO_RCVBUF,(void *)&changed_value,t);	

	unsigned int n2=sizeof(recv_buf);	
	int recv_buf2;
	getsockopt(fd,SOL_SOCKET,SO_RCVBUF,(void *)&recv_buf2,&n2);		
	printf("\nThe default value for receive buffer is %d\n",recv_buf2);	
	close(fd);
	return 0;
}

