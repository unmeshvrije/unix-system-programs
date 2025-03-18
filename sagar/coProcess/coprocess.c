#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

char string[] = "Hellow World ";

int main (int argc,char *argv[])
{
    // variable declaration 
    int count,i;
    int to_parent[2],to_child[2];
    char buf[256];

    pipe(to_parent);
    pipe(to_child);

    if(fork() == 0)
    {
        close(0);
        dup(to_child[0]);
        close(1);
        dup(to_parent[1]);

        close(to_parent[1]);
        close(to_child[0]);
        close(to_parent[0]);
        close(to_child[1]);

        for(;;)
        {
            if((count = read(0,buf,sizeof(buf))) == 0)
            {
                exit(0);
            }
            write(1,buf,count);
        }

    }

    close(1);
    dup(to_child[1]);
    close(0);
    dup(to_parent[0]);

    close(to_child[1]);
    close(to_parent[1]);
    close(to_parent[0]);
    close(to_child[0]);

    for(i=0; i<15;i++)
    {
        write(1,string,strlen(string));
        read(0,buf,sizeof(buf));
    }

    return 0;
}