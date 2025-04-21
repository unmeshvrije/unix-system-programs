#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>

#define LOG_FILE "/tmp/daemon.log"

void daemonize() {
    pid_t pid, sid;

    // Fork the parent process
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        // Parent process exits, leaving child in the background
        exit(EXIT_SUCCESS);
    }

    // Create a new session and detach from terminal
    sid = setsid();
    if (sid < 0) {
        perror("setsid failed");
        exit(EXIT_FAILURE);
    }

    // Change working directory to root
    if (chdir("/") < 0) {
        perror("chdir failed");
        exit(EXIT_FAILURE);
    }

    // Redirect standard file descriptors to /dev/null
    int fd = open("/dev/null", O_RDWR);
    if (fd != -1) {
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        close(fd);
    }

    // Set file permissions to prevent security issues
    umask(0);
}

void write_to_log(const char *message) {
    FILE *log = fopen(LOG_FILE, "a");
    if (log == NULL) return;

    time_t now = time(NULL);
    fprintf(log, "[%s] %s\n", ctime(&now), message);
    fclose(log);
}

void signal_handler(int sig) {
    if (sig == SIGTERM) {
        write_to_log("Daemon terminating.");
        exit(0);
    }
}

int main() {
    // Daemonize the process
    daemonize();

    // Handle termination signals
    signal(SIGTERM, signal_handler);
    signal(SIGHUP, SIG_IGN);

    // Daemon main loop
    while (1) {
        write_to_log("Daemon is running...");
        sleep(5); // Simulate background work
    }

    return 0;
}

