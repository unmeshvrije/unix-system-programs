#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>

#define MAXLINE 1000

int main(int argc, char* argv[]) {

   char buf[MAXLINE];
   pid_t pid;
   int status;

   while (fgets(buf, MAXLINE, stdin) != NULL) {
    if (buf[strlen(buf) - 1] == '\n') {
      buf[strlen(buf) - 1] = 0; /*replace newline with null*/
    }

    if ((pid = fork()) < 0) {
      printf("cannot fork\n");
      exit(1);
    } else if (pid == 0) {
      /* child */
      execlp(buf, buf, (char*) 0);
      printf("could not execute %s", buf);
      exit(127);
    }

    /* parent */
    if ((pid = waitpid(pid, &status, 0)) < 0) {
      printf("could not wait\n");
    }
   }

   exit(0);
}
