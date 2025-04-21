#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int main() {

  register int i;
  int pid;
  pid = setpgrp();

  printf("Parent PID = %d\n", getpid());

  for (i = 0; i < 10; i++) {
    printf("Trying to create a child %d...\n\n", i);

    if (fork() == 0) {
      /* chlid */
      /**
      0000000001 = 1  (3 & 1) = True
      0000000011 = 3
      0000000101 = 5 
      0000000111 = 7
      0000000110 = 6 (6 & 1 = 0 = False)

      */
      if (i & 1) { // bitwise AND
        setpgrp();
      }
      printf("i = %d, pid = %d, pgrp = %d\n", i, getpid(), getpgrp());
      pause();
    } else {
      printf("Child creation failed\n");
    }
  }

  kill(0, SIGINT);

  
  return 0;
}
