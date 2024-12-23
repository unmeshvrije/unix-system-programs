#include<stdio.h>

#include<stdlib.h>
#include<unistd.h>

int main() {

  printf("pid of this process is %ld\n", (long)getpid());
  exit(0);
}

