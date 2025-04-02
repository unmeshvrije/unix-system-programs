#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <time.h>

void wakeup()
{
  printf("Waking up...\n");
}

int main(int argc, char *argv[])
{
    struct stat statbuf;
    time_t axtime;

    if(argc != 2)
    {
        printf("Only 1 arg\n");
        exit(-1);
    }

    axtime = (time_t)0;

    for(;;)
    {
        /* find out file access time */

        if(stat(argv[1], &statbuf) == -1)
        {
            printf("File %s not there\n", argv[1]);
            exit(-2);
        }
        if(axtime != statbuf.st_atime)
        {
            printf("File %s accessed at %s\n", argv[1], ctime(&axtime));
            axtime = statbuf.st_atime;
        }

        signal(SIGALRM, wakeup); /* reset for alaram */
        alarm(30);
        pause(); /* sleep until signal */
    }

    return 0;
}

