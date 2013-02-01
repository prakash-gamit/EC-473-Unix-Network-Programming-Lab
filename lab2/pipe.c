#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void sort(int arr[], int len)
{
  int i, j;
  for(i=0; i< len - 1; i++)
  {
    for(j=0; j<len - 1 - i; j++)
    {
      if(arr[j] > arr[j+1])
        swap(&arr[j], &arr[j+1]);
    }
  }
}

/*
 * 
 */

int main(int argc, char** argv) {

  int n, num;
  int fd[2], fd2[2];
  pid_t pid;
  int MAXLINE = 1024;
  char line[MAXLINE];
  int arr[] = {50, 41, 32, 24, 11, 9, 2, 23, 50, 12, 34, 79, 95, 83, 63, 55};
  int len=16;

  if(pipe(fd) < 0){
    perror("pipe error\n");
    exit(1);
  }

  if(pipe(fd2) < 0){
    perror("pipe error\n");
    exit(1);
  }

  if((pid = fork()) < 0){
    perror("fork error\n");
    exit(1);
  }
  else if(pid > 0){/* parent */
    close(fd[0]);
    close(fd2[1]);
    printf("parent\n");
    int i;
    char str[1024] = "";
    sprintf(str, "%d", len);
    write(fd[1], str, sizeof(str));

    for(i=0; i<len; i++){
      sprintf(str, "%d", arr[i]);
      write(fd[1], str, sizeof(str));
    }
    write(fd[1], "quit", 4);

    n = read(fd2[0], line, MAXLINE);
    while(strcmp(line, "quit") != 0){
      printf("%s\n", line);
      n = read(fd2[0], line, MAXLINE);
    }
  }
  else{
    close(fd[1]);
    close(fd2[0]);
    printf("child\n");
    n = read(fd[0], line, MAXLINE);
    int l = atoi(line);
    int array[l];

    n = read(fd[0], line, MAXLINE);
    int k = 0;
    while(strcmp(line, "quit") != 0){
      num = atoi(line);
      array[k] = num;
      k++;
      n = read(fd[0], line, MAXLINE);
    }
    sort(array, l);
    char str[1024]="";
    for(k=0; k<l; k++){
      sprintf(str, "%d", array[k]);
      write(fd2[1], str, sizeof(str));
    }
    write(fd2[1], "quit", 4);
  }

  return 0;
}

