#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/uio.h>
#include<fcntl.h>
#include<unistd.h>

int main(void) {

  int fd;
  int bytes_read;
  char buf[51200];
  fd = open("./delme.txt", O_RDONLY);
 
  printf("fd = %d\n", fd);
  bytes_read = read(fd, buf, sizeof(buf));
  printf("%d bytes read: %s\n", bytes_read, buf);
  printf("________\n");

  // 1 sec = 1000000
  //usleep(500000);
  sleep(5);
  bytes_read = read(fd, buf, sizeof(buf));
  printf("%d bytes read: %s\n", bytes_read, buf);
  bytes_read = read(fd, buf, sizeof(buf));
  printf("%d bytes read: %s\n", bytes_read, buf);
  printf("________\n");
  bytes_read = read(fd, buf, sizeof(buf));
  printf("%d bytes read: %s\n", bytes_read, buf);
  bytes_read = read(fd, buf, sizeof(buf));
  printf("%d bytes read: %s\n", bytes_read, buf);
  printf("________\n");
  bytes_read = read(fd, buf, sizeof(buf));
  printf("%d bytes read: %s\n", bytes_read, buf);
  bytes_read = read(fd, buf, sizeof(buf));
  printf("%d bytes read: %s\n", bytes_read, buf);
  printf("________\n");
  bytes_read = read(fd, buf, sizeof(buf));
  printf("%d bytes read: %s\n", bytes_read, buf);
}
