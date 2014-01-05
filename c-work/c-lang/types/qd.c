/*
 * Demonstrate qualifiers used in function declaration array formal parameters.
 */
#include <stdio.h>

static void dump_list(int a[static 10], size_t len);
static void print_list(int a[*]);

int main(void) {
    dump_list(NULL, 0);
    int a[9];
    dump_list(a, 9);
    int b[12];
    dump_list(b, 12);
    int c[10];
    dump_list(c, 10);

    return 0;
}

static void dump_list(int a[], size_t len) {
    for (int i = 0; i < len; i++) {
        static char *sep = "";
        printf("%d%s", a[i], sep);
        sep = " ";
    }
    printf("\n");
}

static void print_list(int a[]) {
}
