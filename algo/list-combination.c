#include <stdio.h>

void list_combination(int a[], size_t n) {
    for (int i = 0; i < (1 << n); i++) {
        int printed = 0;
        char *sep = "";
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 0x01) {
                printed = 1;
                printf("%s%d", sep, a[j]);
                sep = ", ";
            }
        }
        if (printed) {
            printf("\n");
        }
    }
}

int main() {
    int a[] = {1, 2, 3};

    list_combination(a, 3);

    int b[] = {7, 9, 11, 13, 17, 19, 23, 29};
    list_combination(b, sizeof(b)/sizeof(b[0]));

    return 0;
}
