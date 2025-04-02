#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/signal.h>

unsigned short int buffer[4096] = {0};

int main(void)
{
    int offset, endof, scale, eff, gee, text;
    extern void theend(), f(), g();
    signal(SIGINT, theend);
    endof = (int)theend;
    offset = (int)main;

    /* calculates naumber of words of program text */
    text = (endof - offset + sizeof(int) - 1) / sizeof(int);
    scale = 0xffff;
    printf("Offset %d endof %d text %d\n", offset, endof, text);
    eff = (int)f;
    gee = (int)g;
    printf("f %d g %d fdiff %d gdiff %d\n", eff, gee, eff-offset, gee-offset);
    profil(buffer, sizeof(int) * text, offset, scale);

    for(;;)
    {
        f();
        g();
    }

    return 0;
}

void f()
{}

void g()
{}

void theend()
{
    int i;
    for(i = 0; i < 4096; i++)
        if(buffer[i])
            printf("buf[%d] = %d\n", i, buffer[i]);
    
    exit(0);
}
