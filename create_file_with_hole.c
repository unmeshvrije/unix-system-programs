#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

char buf1[] = "abcdeghij";
char buf2[] = "ABCDEGHIJ";

int main(void)
{
   int fd;
   if((fd = creat("file.hole",O_CREAT| O_RDWR))<0)
      printf("creat err ");
   if(write(fd,buf1,10) != 10)
      printf("buf1 wrie error ");
   if(lseek(fd,16384,SEEK_SET) == -1)
      printf("lseek error");
   if(write(fd,buf2,10)!= 10)
     printf("buf2 write error");
   exit(0);
}
