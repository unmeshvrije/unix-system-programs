#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <signal.h>

// Global and static variables to increase memory usage
static int static_var = 42;
int global_var = 100;

void handle_signal(int sig) {
    printf("Received signal: %d\n", sig);
}

void print_usage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    
    printf("User CPU time used: %ld.%06d sec\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
    printf("System CPU time used: %ld.%06d sec\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
    printf("Maximum resident set size: %ld KB\n", usage.ru_maxrss);
    printf("Integral shared text memory size: %ld KB\n", usage.ru_ixrss);
    printf("Integral unshared data size: %ld KB\n", usage.ru_idrss);
    printf("Integral unshared stack size: %ld KB\n", usage.ru_isrss);
    printf("Page reclaims (soft page faults): %ld\n", usage.ru_minflt);
    printf("Page faults (hard page faults): %ld\n", usage.ru_majflt);
    printf("Swaps: %ld\n", usage.ru_nswap);
    printf("Block input operations: %ld\n", usage.ru_inblock);
    printf("Block output operations: %ld\n", usage.ru_oublock);
    printf("Messages sent: %ld\n", usage.ru_msgsnd);
    printf("Messages received: %ld\n", usage.ru_msgrcv);
    printf("Signals received: %ld\n", usage.ru_nsignals);
    printf("Voluntary context switches: %ld\n", usage.ru_nvcsw);
    printf("Involuntary context switches: %ld\n", usage.ru_nivcsw);
}

int main() {
    struct timeval start, end;
    gettimeofday(&start, NULL);
    
    // Register signal handler
    signal(SIGUSR1, handle_signal);
    
    // Allocate memory to increase resource usage
    int *dynamic_array = (int *)malloc(100000 * sizeof(int));
    for (int i = 0; i < 100000; i++) {
        dynamic_array[i] = i;
    }
    
    // Simulate workload
    for (volatile long i = 0; i < 100000000; i++);
    
    // Send signal to self
    raise(SIGUSR1);
    
    gettimeofday(&end, NULL);
    
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
    printf("Elapsed time: %.6f seconds\n", elapsed);
    
    print_usage();
    
    free(dynamic_array);
    
    return 0;
}

