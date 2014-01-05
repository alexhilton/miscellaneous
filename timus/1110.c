#include <stdio.h>

/*
 * brute force might get it.
 * be cautious about overflowing when calculate x^n
 */
int main() {
    int n, m, y, x;
    while (scanf("%d%d%d", &n, &m, &y) != EOF) {
        if (y >= m) {
            printf("-1\n");
            continue;
        }
        int found = 0;
        for (x = 0; x < m; x++) {
            int k = x;
            int j = 1;
            for (j = 2; j <= n; j++) {
                k *= x;
                k %= m;
            }
            if (k % m == y) {
                found = 1;
                printf("%d ", x);
            }
        }
        if (!found) {
            printf("-1");
        }
        printf("\n");
    }
    return 0;
}
