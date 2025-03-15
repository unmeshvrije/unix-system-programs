#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main() {
  const void *p = sbrk(0);
  printf("My program break is at %p\n", p);

  const void* q = sbrk(25600);
  printf("My program break is now at %p\n", q);

  const void* r = sbrk(0);
  printf("My program break is now at %p\n", r);

  return 0;
}
