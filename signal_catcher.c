#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>


void sigcatcher() {
  printf("Process %d caught one!\n", getpid());
  signal(SIGINT, sigcatcher);
}


int main(int argc, char *argv[]) {

  int ppid;
  signal(SIGINT, sigcatcher);
  raise(SIGINT); 

  return 0;
}
