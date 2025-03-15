#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

char string [] = "Hello World";

int main(int argc, char* argv[]) {

  int count, i;
  int to_parent[2], to_child[2];
  char buf[256];

  /* Create two pipes */

  pipe(to_parent); // [0] reader FD [1] write FD
  pipe(to_child);

  if (fork() == 0) {
    /* Child executes here */

    close(0) ; // close stdin
    dup(to_child[0]); // dup child-pipe read to stdin
    close(1); // close stdout
    dup(to_parent[1]); // dup parent-pipe write to stdout

    close(to_parent[1]); // Close opposite side's FD first
    close(to_child[0]);
    close(to_parent[0]);
    close(to_child[1]);

      for (;;) {
        if ((count = read(0, buf, sizeof(buf))) == 0) {
          exit(0);
        }
        write(1, buf, count);
      }
    }

    /* Parent executes here */

    close(1); // close stdout
    dup(to_child[1]);
    close(0);
    dup(to_parent[0]);

    close(to_child[1]);
    close(to_parent[0]);
    close(to_parent[1]);
    close(to_child[0]);

    for (i = 0; i < 15; ++i) {
      write(1, string, strlen(string));
      read(0, buf, sizeof(buf));
    }

  return 0;
}

