#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>


int main(int argc, char *argv[])
{
    int fd;
    int ret;

    printf("%s\n",argv[1]);
    ret = chroot(argv[1]);
    printf("chroot return %d \n",ret);

    fd = open("/temp/a/b/c/sagar",O_RDONLY);
    printf("opening consrnt return = %d \n",fd);

    return 0;
}