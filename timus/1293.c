#include <stdio.h>

int main() {
    int n, a, b;
    while (scanf("%d%d%d", &n, &a, &b) != EOF) {
        int r = n * a * b * 2;
        printf("%d\n", r);
    }

    return 0;
}
