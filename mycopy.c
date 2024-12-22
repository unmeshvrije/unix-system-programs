#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

char buffer[2048]; // 2 ^ 11
int version = 1; // Chapter 2 explains this

void copy(int old, int new) {
  int count;

  while ((count = read(old, buffer, sizeof(buffer))) > 0) {
    printf("%d characters copied\n", count);
    write(new, buffer, count);
  }
}

int main(int argc, char* argv[]) {

  int fdold, fdnew;

  if (argc != 3) {
    printf("need 2 arguments for copy program\n");
    exit(1);
  }

  fdold = open(argv[1], O_RDONLY);
  if (-1 == fdold) {
    printf("cannot open file %s\n", argv[1]);
    exit(1);
  }

  // 0777 gives r,w,execute permission to all
  fdnew = creat(argv[2], 0666); // 6 = 2,4 // Create target file with rw permissions for all
  if (-1 == fdnew) {
    printf("cannot open file %s\n", argv[2]);
    exit(1);
  }

  copy(fdold, fdnew);
 
  // Not closing a previously opened file is a sin!
  close(fdold);
  close(fdnew);
  exit(0);
}
