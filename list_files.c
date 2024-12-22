#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>

int main(int argc, char *argv[]) {
  DIR *dp;
  struct dirent * dirp;
 /*
 struct dirent {
      int fd,
      char* d_name;
      ...
 }
 */
  printf("Running %s\n", argv[0]);

  if ((dp = opendir(argv[1])) == NULL) {
    printf("Cannot open %s", argv[1]);
    exit(1);
  }

  while ((dirp = readdir(dp)) != NULL) {
    printf("%s\n", dirp->d_name);
  }

  closedir(dp);
  exit(0);
}
