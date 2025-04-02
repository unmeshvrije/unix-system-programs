#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int i, * ip;
    extern void f(), sigcatch(int);

    ip = (int*)f;
    for (i = 0; i < 20; i++)
        signal(i, sigcatch);

    *ip = 1;
    printf("after assign to ip\n");
    f();
}

void f()
{
}

void sigcatch(int n)
{
    printf("caught sig %d\n", n);
    exit(1);
}