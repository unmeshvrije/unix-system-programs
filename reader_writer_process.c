#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_SIZE 512

void process_A() {
    int fd;
    char buf[BUF_SIZE];

    fd = open("testfile.txt", O_RDONLY);
    if (fd < 0) {
        perror("Error opening file in A");
        exit(1);
    }

    read(fd, buf, sizeof(buf)); 
    printf("Process A First read: %s\n", buf);

    read(fd, buf, sizeof(buf));
    printf("Process A Second read: %s\n", buf);

    close(fd);
}

void process_B() {
    int fd;
    char buf[BUF_SIZE];

    
    for (int i = 0; i < sizeof(buf); i++) {
        buf[i] = 'a';
    }

   
    fd = open("testfile.txt", O_WRONLY | O_CREAT, 0644);
    if (fd < 0) {
        perror("Error opening file in B");
        exit(1);
    }

    
    write(fd, buf, sizeof(buf));
    printf("Process B First write done\n");

    write(fd, buf, sizeof(buf));
    printf("Process B Second write done\n");

    close(fd);
}

int main() {
    int pid = fork(); 

    if (pid == 0) {
        process_A(); 
    } else if (pid > 0) {
        process_B(); 
    } else {
        perror("Fork failed");
        exit(1);
    }

    return 0;
}
