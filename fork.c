#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char *argv[]) {
  if (fork() == 0) {
    /* child */
    execl("mycopy", "mycopy", argv[1], argv[2], 0);
  }

  /* parent */
  wait((int*)0);
  printf("copy done\n");
  //exit
}
