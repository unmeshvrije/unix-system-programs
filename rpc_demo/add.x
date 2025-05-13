/* add.x */
program ADD_PROG {
    version ADD_VERS {
        int ADD(intpair) = 1;
    } = 1;
} = 0x31234567;

struct intpair {
    int a;
    int b;
};
