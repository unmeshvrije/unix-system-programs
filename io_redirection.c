#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char *argv[]) {
  int num;
  printf("Enter a num:\n");

  read(0, &num, sizeof(int));

  write(1, &num, sizeof(int));

  printf("\n");

  exit(0);
}
