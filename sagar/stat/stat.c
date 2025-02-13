#include<stdio.h>
#include<sys/stat.h>

int main(int argc,char *argv[])
{
    struct stat fst;
    stat(argv[1],&fst);
    printf("inode number  : %llu \n",fst.st_ino);
    printf("mode          : %o \n",fst.st_mode);

    return 0;
}