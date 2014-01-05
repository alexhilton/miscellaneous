#include <stdio.h>

int main() {
    int a, b;
    while (scanf("%d%d", &a, &b) != EOF) {
        int m, n;
        if (a == 0) {
            n = 0;
        } else {
            n = a - 1;
        }
        if (b == 0) {
            m = 0;
        } else {
            m = b - 1;
        }
        printf("%d %d\n", m, n);
    }

    return 0;
}
