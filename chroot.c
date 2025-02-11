#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

int main(int argc, char* argv[]) {

  /*
    ./temp/a/b/c/consent

    IF "temp" becomes root,
    then /a/b/c/consent is accessible
  */
  int fd;
  int ret;
  printf("%s\n", argv[1]);

  ret = chroot(argv[1]);
  printf("chroot returned %d\n", ret);

  fd = open("/temp/a/b/c/consent", O_RDONLY);
  printf("Opening consent, returned = %d\n", fd);

  return 0;
}
