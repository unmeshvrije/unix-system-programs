#include<stdio.h>
#include<stdlib.h>

int main(void) {

  int num = 0x0A0B0C0D;
  /*
    0A 0B 0C 0D
    high     low
  */
  unsigned char *ptr = (unsigned char*)&num;

  if (*ptr == 0x0D) {
    printf("Little endian\n");
  } else {
    printf("Big endian\n");
  }
  return 0;
}
