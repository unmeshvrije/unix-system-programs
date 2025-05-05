#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <signal.h>

#define SOCKET_PATH "/tmp/unix_socket_example"
#define BUFFER_SIZE 128

void handle_client(int client_fd) {
    char buffer[BUFFER_SIZE] = {0};

    read(client_fd, buffer, BUFFER_SIZE);
    printf("Client says: %s\n", buffer);

    const char *response = "Hello from server (multi-client)";
    write(client_fd, response, strlen(response));

    close(client_fd);
    exit(0);  // End child process
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_un addr;

    // Cleanup any existing socket
    unlink(SOCKET_PATH);

    // Optional: avoid zombie processes
    signal(SIGCHLD, SIG_IGN);

    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) < 0) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Multi-client server listening at %s\n", SOCKET_PATH);

    while (1) {
        client_fd = accept(server_fd, NULL, NULL);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            close(client_fd);
        } else if (pid == 0) {
            // Child process
            close(server_fd); // Child doesn't need server socket
            handle_client(client_fd);
        } else {
            // Parent process
            close(client_fd); // Parent doesn't need client socket
        }
    }

    close(server_fd);
    unlink(SOCKET_PATH);
    return 0;
}

