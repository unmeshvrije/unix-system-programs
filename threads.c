#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t stop_thread = 0;

void handle_signal(int signal) {
    stop_thread = 1;
}

void* increment_counter(void* arg) {
    int* counter = (int*)arg;
    while (!stop_thread) {
        (*counter)++;
        printf("Counter: %d\n", *counter);
        sleep(1); // Sleep for 1 second
    }
    return NULL;
}

int main() {
    int counter = 0;
    pthread_t thread_id;

    signal(SIGINT, handle_signal);

    if (pthread_create(&thread_id, NULL, increment_counter, &counter) != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        if (stop_thread) {
            break; // Exit if signal received
        }
        sleep(1);
    }

    stop_thread = 1;

    pthread_join(thread_id, NULL);

    printf("Final Counter Value: %d\n", counter);
    return 0;
}
