#include <stdio.h>
#include <stdlib.h>
#include "add.h"

int main(int argc, char *argv[]) {
    CLIENT *clnt;
    intpair pair;
    int *result;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <server_host> <int1> <int2>\n", argv[0]);
        exit(1);
    }

    clnt = clnt_create(argv[1], ADD_PROG, ADD_VERS, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror(argv[1]);
        exit(1);
    }

    pair.a = atoi(argv[2]);
    pair.b = atoi(argv[3]);

    result = add_1(&pair, clnt);
    if (result == NULL) {
        clnt_perror(clnt, "call failed");
    } else {
        printf("Result: %d\n", *result);
    }

    clnt_destroy(clnt);
    return 0;
}
