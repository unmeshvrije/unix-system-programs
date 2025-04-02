#include<sys/types.h>
#include<sys/times.h>

extern long times()

int main()
{
    int i;
    struct tms pb1,pb2;
    long pt1,pt2;

    pt1 = times(&pb1);

    for(i = 0;i < 10 ;i++)
       if(fork() == 0)
          child(i);
    
    for(i = 0; i < 10; i++)
       wait((int *)0);
    
    pt2 = times(&pb2);
    printf("parent real %u user %u sys %u cuser %u csys %u\n",
    pt2-pt1,pb2.tms_utime - pb1.tms_utime,pb2.tms_stime - pb1.tms_stime,
    pb2.tms_cutime - pb1.tms_cutime,pb2.tms_cstime - pb1.tms_cstime);

}
void child(int n)
{
    int i;
    struct tms cb1,cb2;
    long t1,t2;

    t1 = times(&cb1);
    for(i = 0; i< 10000; i++)
        ;
    t2 = times(&cb2);
    printf("child %d : real %u user %u sys %u \n",n,t2-t1,
    cb2.tms_utime - cb1.tms_utime,cb2.tms_stime - cb1.tms_stime);

    exit();

}