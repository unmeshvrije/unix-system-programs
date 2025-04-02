#include<sys/types.h>
#include<sys/stat.h>
#include<sys/signal.h>


int main(int argc,char *argv[])
{
    extern unsigned alarm();
    extern void  wakeup();
    struct stat statbuf;
    time_t axtime;

    if(argc != 2)
    {
        printf("only 1 arg \n");
        exit();
    }

    axtime = (time_t)0;
    for(;;)
    {
        // find out access time
        if(stat(argv[1],&statbuf) == -1)
        {
            printf("files %s not there \n",argv[1]);
            exit();
        }
        if(axtime != statbuf.st_atime)
        {
            printf("file %s accessed \n",argv[1]);
            axtime =  statbuf.st_atime;
        }

        signal(SIGALRM,wakeup);
        alarm(60);
        pause();
    }

}

void wakeup()
{

}