#include<unistd.h>
#include<sys/mkdev.h>

int main(int argc, char *argv[])
{
    int i;
    struct stat byf;

    for(i = 1;i < argc;i++)
    {
        printf("%s : \n",argv[i]);
        if(stat(argv[i] &buf)<0)
        {
            err_ret("stat error");
            continue;

        }
        printf("dev= %d/%d ",major(buf.st_dev),minor(buf.st_dev));

        if(S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
        {
            printf("  (%s) rdev = %d/%d",(S_ISCHR(buf.st_mode)) ? "character" : "block",major(buf.st_rdev),minor(buf.st_rdev));
        }
        printf("\n\n");
    }
    exit(0);
}