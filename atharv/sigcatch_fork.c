#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
void sigcatcher(int signo) {
    printf("Process %d caught%d\n", getpid(), signo);signal(SIGUSR1, sigcatcher);  
}

int main() {
    signal(SIGUSR1, sigcatcher);
    if (fork() == 0) { 
        kill(getppid(), SIGUSR1);
    }
    sleep(2);
    return 0;
}
