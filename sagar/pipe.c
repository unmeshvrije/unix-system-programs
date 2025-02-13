#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>

int main(void){
    int n;
    int fd[2];
    pid_t pid;
    char line[1024];

    if(pipe(fd) < 0)
    {
        printf("cannot create pipe");
        return -1;
    }

    if((pid = fork()) < 0)
    {
        printf("we are in china");
        return -1;
    }
    else if(pid > 0)
    {
        close(fd[0]);
        printf("from paremt \n");
        write(fd[1],"kuth hotas!\n",13);
    }
    else{
        close(fd[1]);
        n = read(fd[0],line,1024);
        write(1,line,n);
    }
    
    return 0;
}

