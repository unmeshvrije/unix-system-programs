#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>


int main(void) {
  /*Page 537, W. Richard Stevens*/
  int n;
  int fd[2];
  pid_t pid;
  char line[1024];

  if (pipe(fd) < 0) {
    printf("Cannot create pipe");
    return -1;
  }

  if ((pid = fork()) < 0) {
    printf("we are in china!");
    return -1;
  } else if (pid > 0) {
    /* parent */
    close(fd[0]); // parent who does not want to listen/read
    printf("From parent...\n");
    write(fd[1], "Kuthe hotas!\n", 13);
  } else {
    /* child */
    close(fd[1]);
    n = read(fd[0], line, 1024);
    write(1, line, n);
  }

  return 0;
}

