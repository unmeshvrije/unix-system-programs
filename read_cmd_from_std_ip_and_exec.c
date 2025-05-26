#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>


#define MAXSIZE 4096
int main(void)
{
   char buf[MAXSIZE] ;
   pid_t pid;
   int status;
   printf("%%");
   while(fgets(buf,MAXSIZE,stdin)!= NULL)
     {
     if(buf[strlen(buf) - 1 ] == '\n')
         buf[strlen(buf)-1] = 0;
     if((pid = fork()) < 0)
      {
        printf("fork error");
     }
     else if(pid == 0)
    {
       execlp(buf,buf,(char *)0);
       printf("could not execute %s",buf);
       exit(127);
    }
    
    /* parent */
    if((pid = waitpid(pid,&status,0)) < 0)
       printf(" wiatpid error");
    printf("%%");
   }
  exit(0);
}
