#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {

  int hex_num = 0x10; // 0x allows us to declare a Hex number
  printf("num = %d\n", hex_num);

  int octal_num = 010;
  printf("num = %d\n", octal_num);

  exit(0);
}
