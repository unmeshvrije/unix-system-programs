#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
static void sig_alrm(int signo)
{
   // nothing to do , just returning wake up sigsuspend()
}

unsigned int sleep(unsigned int nsecs)
{
    struct sigaction newact,oldact;
    sigset_t newmask,oldmask,suspmask;
    unsigned int unslept ;

    newact.sa_handler = sig_alrm;
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = 0 ;
    sigaction(SIGALRM,&newact,&oldact);

    sigemptyset(&newmask);
    sigaddset(&newmask,SIGALRM);
    sigprocmask(SIG_BLOCK,&newmask,&oldmask);
    alarm(nsecs);
    
    suspmask = oldmask;
    sigdelset(&suspmask,SIGALRM);
    sigsuspend(&suspmask);

    unslept = alarm(0);
    sigaction(SIGALRM,&oldact,NULL);

    sigprocmask(SIG_SETMASK,&oldmask,NULL);
    return(unslept);

}

int main()
{
    printf("before");
    sleep(4000);
    printf("after ");
}