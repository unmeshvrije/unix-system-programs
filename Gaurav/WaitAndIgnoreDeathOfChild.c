#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    int i, ret_val, ret_code;
    if(argc > 1)
        signal(SIGCLD, SIG_IGN);
    
    for(i = 0; i < 15; i++)
    {
        if(fork() == 0)
        {
            printf("child proc %x\n", getpid());
            exit(i);
        }
    }

    ret_val = wait(&ret_code);
    printf("Wait ret_val %x ret_code %x\n", ret_val, ret_code);
    return(0);
}