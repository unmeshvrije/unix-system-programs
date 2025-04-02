#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(void) {
  int fd, i;

  int bytes_written;
  char buf[51200];
  for (i = 0; i < sizeof(buf); i++) {
    buf[i] = 'a';
  }

  fd = open("./delme.txt", O_WRONLY | O_CREAT, 0777);
  bytes_written = write(fd, buf, sizeof(buf));
  printf("%d bytes written\n", bytes_written);
  printf("_______\n");
  bytes_written = write(fd, buf, sizeof(buf));
  printf("%d bytes written\n", bytes_written);
  bytes_written = write(fd, buf, sizeof(buf));
  printf("%d bytes written\n", bytes_written);
  printf("_______\n");
  bytes_written = write(fd, buf, sizeof(buf));
  printf("%d bytes written\n", bytes_written);
  bytes_written = write(fd, buf, sizeof(buf));
  printf("%d bytes written\n", bytes_written);
  printf("_______\n");
  bytes_written = write(fd, buf, sizeof(buf));
  printf("%d bytes written\n", bytes_written);
  bytes_written = write(fd, buf, sizeof(buf));
  printf("%d bytes written\n", bytes_written);
  printf("_______\n");
  bytes_written = write(fd, buf, sizeof(buf));

  printf("%d bytes written\n", bytes_written);
  close(fd);
}
