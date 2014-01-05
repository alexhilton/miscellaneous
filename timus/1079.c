/*
 * Timus problem 1079
 */
#include <stdio.h>

/*
 * Brute force version. Calculate sequence of a, then for each n, find its max.
 * Cannot use recursion directly. It will calculate same value repeatedly which will
 * exceed time limit.
 */
int main() {
    int n;
    /* It is hard to believe we can make such a large array */
    int a[100000];
    a[0] = 0;
    a[1] = 1;
    for (int i = 1; i < 50000; i++) {
        a[2*i] = a[i];
        a[2*i + 1] = a[i] + a[i+1];
    }
    scanf("%d", &n);
    while (n != 0) {
        int max = -1;
        for (int i = 0; i <= n; i++) {
            if (max < a[i]) {
                max = a[i];
            }
        }
        printf("%d\n", max);
        scanf("%d", &n);
    }

    return 0;
}
