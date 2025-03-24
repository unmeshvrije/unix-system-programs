#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigCatch(int signo)
{
    printf("User defined message PId %d : signal number : %d\n", getpid(), signo);
    signal(SIGUSR1, sigCatch);
}

int main(void)
{
    signal(SIGUSR1, sigCatch);
    if (fork() == 0)
    {
        kill(getppid(), SIGUSR1);
    }

    pause();
    return(0);
}