#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define BUFSIZE 4096

int main(void)
{
  int n;
  char buf[BUFSIZE];
  while((n  = read(STDIN_FILENO,buf,BUFSIZE))>0)
     if(write(STDOUT_FILENO,buf,n)!=n)
        printf("write error");
     if(n <0)
        printf(" read error");
    exit(0);
}


