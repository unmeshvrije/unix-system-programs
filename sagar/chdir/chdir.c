#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


int main(int argc,char *argv[])
{
    if(argc < 2)
    {
        printf("please pass directory as parameter \n");
        return 1;
    }
    char buf[1024];
    getcwd(buf,1024);
    printf("current directory is  %s \n",buf);
    printf("changing directory to %s ... \n",argv[1]);
    chdir(argv[1]);

    getcwd(buf,1024);
    printf("current direcoty is %s\n",buf);

    return 0;
}
