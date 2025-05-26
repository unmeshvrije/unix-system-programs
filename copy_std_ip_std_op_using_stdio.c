#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(void)
{
   int c;
   while((c = getc(stdin)) != EOF)
        if(putc(c,stdout) == EOF) 
         printf("o/p err");
   if(ferror(stdin))
      printf("input err");
   exit(0);
}
