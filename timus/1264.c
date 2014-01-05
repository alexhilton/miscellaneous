#include <stdio.h>

/*
 * It is fucking ridiculous
 * if m, n are ints, WA.
 * If long, AC.
 * test data are larger than 40000, perhaps.
 */
int main() {
    long n, m;
    while (scanf("%ld%ld", &n, &m) != EOF) {
        long long p = n * (m + 1);
        printf("%lld\n", p);
    }

    return 0;
}
