#include<unistd.h>

static void sig_usr(int);
int main(void)
{
    if(signal(SIGUSR1,sig_usr) == SIG_ERR)
       printf("can not catch sigusr1 ");
    if(signal(SIGUSR2,sig_usr) == SIG_ERR)
      printf("can not catch sigusr2");
    for(;;)
       pause();
}

static void sig_usr(int signo)
{
    if(signo == SIGUSR1)
         printf("got siguser1 ");
   else if(signo == SIGUSR2)
       printf("got siguser 2\n");
   else 
      printf("recevird sig %d \n",signo);
}