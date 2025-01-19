#include <stdio.h>
#include <stdlib.h>
#include <sys/sysctl.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/user.h>
#include <string.h>
#include <errno.h>

int main(void) {
    int mib[3];
    struct kinfo_proc *procs = NULL;
    size_t size = 0;

    // MIB array: [CTL_KERN, KERN_PROC, KERN_PROC_ALL]
    // This will query all running processes.
    mib[0] = CTL_KERN;
    mib[1] = KERN_PROC;
    mib[2] = KERN_PROC_ALL;

    // First call with a NULL buffer to get the size needed.
    if (sysctl(mib, 3, NULL, &size, NULL, 0) == -1) {
        fprintf(stderr, "sysctl (get size) failed: %s\n", strerror(errno));
        return 1;
    }

    // Allocate a buffer large enough to hold the process list.
    procs = (struct kinfo_proc *)malloc(size);
    if (!procs) {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }

    // Second call gets the actual process data.
    if (sysctl(mib, 3, procs, &size, NULL, 0) == -1) {
        fprintf(stderr, "sysctl (get data) failed: %s\n", strerror(errno));
        free(procs);
        return 1;
    }

    // Number of processes returned
    int count = (int)(size / sizeof(struct kinfo_proc));

    // Print a simple header
    printf("%5s  %-16s  %5s\n", "PID", "COMMAND", "STATE");
    printf("------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        // Extract PID and command name
        pid_t pid = procs[i].kp_proc.p_pid;
        char  comm[MAXCOMLEN+1];
        strncpy(comm, procs[i].kp_proc.p_comm, MAXCOMLEN);
        comm[MAXCOMLEN] = '\0';

        // The process state is in p_stat (numeric on macOS).
        // Some typical BSD states (historical):
        //  1=SIDL (startup), 2=SRUN (running), 3=SSLEEP, 4=SSTOP, 5=SZOMB, etc.
        int state = procs[i].kp_proc.p_stat;

        printf("%5d  %-16s  %5d\n", pid, comm, state);
    }

    free(procs);
    return 0;
}
