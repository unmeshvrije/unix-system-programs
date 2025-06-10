#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
int main(void)
{
   if(open("tempfile",O_RDWR)<0)
      printf("open error");
   if(unlink("tempfile")<0)
      printf("unlink error");
   printf("file unlinked \n");
   sleep(15);
   printf("done \n");
   exit(0);
}
