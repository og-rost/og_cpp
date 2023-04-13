/*

Big-endian is an order in which the "big end" (most significant value in the sequence) is stored first, at the lowest storage address.
Little-endian is an order in which the "little end" (least significant value in the sequence) is stored first.

*/

void show_mem_rep(char* start, int n) {
    int i;
    for (i = 0; i < n; ++i) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

/*

int i = 0x01234567;
show_mem_rep output on little endian machine 67 45 23 01
show_mem_rep output on big    endian machine 01 23 45 67

*/

/****************************************/

void print_endianness() {
    unsigned int i = 1;
    char *c = (char*)&i;
    if (*c) {
        printf("Little endian");
    } else {
        printf("Big endian");
    }
}