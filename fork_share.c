#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>


int fdrd, fdwt;
char c;

void rdwrt() {
  for (;;) {
    if (read (fdrd, &c, 1) != 1) {
      return;
    }
    write(fdwt, &c, 1);
  }
}

int main(int argc, char* argv[]) {

  if (argc != 3) {
    exit(1);
  }

  if ((fdrd = open(argv[1], O_RDONLY)) == -1) {
    exit(1);
  }

  if ((fdwt = creat(argv[2], 0666)) == -1) {
    exit(1);
  }

  fork();
  /* Both parent and child execute the same code */

  rdwrt();

  return 0;
}

