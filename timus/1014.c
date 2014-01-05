#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
 * Q is abc, where a*b*c = N
 * To make Q mininal, we should make each a, b and c minial and indivisible. each factor should be < 10,
 * because each factor gonna be a digit. And There is no order, so should make the number of factors minimal.
 * Conditions:
 *    1. each factor is < 10
 *    2. the number of factors is minimal
 *    3. if N is prime, -1
 *    4. if N has a prime factor > 7(next prime is 11, which can not be a digit), -1.
 * So, we need to prime factorization of N., In fact, we need to make:
 * N = 2^x*3^y*5^z*7^w;
 * Then reform them to digits by digit < 10, number of digits is minimal, make one of digits as least as possible
 * For 5^z*7^w, z 5s and w 7s, because any multiply would exceed 10.
 * For 2^x*3^y, first there are y/2 9s. there are x/3 8s. for the rest of 2^m*3^n, if n != 0, we got 2^(m-1), 6;
 * if n == 0, we got 2^m. 
 * Then sort digits ascending and sum final result. use long long to avoid overflowing.
 *
 * Special values:
 * 0, 0*x, so miminal positive(0 is not positive) would be 1*0 = 10
 * 1, it is 1(I don't understand why).
 * N < 10, would be 1 * N, so 10+N.
 * other values, following algo.
 */
int cmp(const void *a1, const void *a2) {
    return *(int *) a1 - *(int *) a2;
}

int main(void) {
    long n;
    scanf("%ld", &n);
    if (n == 0) {
        printf("10\n");
        return 0;
    }
    if (n == 1) {
        printf("1\n");
        return 0;
    }
    if (n < 10) {
        printf("%ld\n", (10+n));
        return 0;
    } else if (n == 10) {
        printf("25\n");
        return 0;
    } else if (n == 11 || n == 13 || n == 17 || n == 19) {
        printf("-1\n");
        return 0;
    }

    int p[4] = {2, 3, 5, 7};
    int a[4];
    int k = 4;
    for (int i = 0; i < 4; i++) {
        a[i] = 0;
        while (n % p[i] == 0) {
            a[i]++;
            n /= p[i];
        }
    }
    /* there are other prime factor, which is > 10, cannot be a digit */
    if (n > 1) {
        printf("-1\n");
        return 0;
    }
#ifndef ONLINE_JUDGE
    for (int i = 0; i < k; i++) {
        if (a[i] != 0) {
            printf("{%d, %d}, ", p[i], a[i]);
        }
    }
    printf("\n");
#endif
    int q[10000];
    int count = 0;
    while (a[3]-- > 0) {
        q[count++] = p[3];
    }
    while (a[2]-- > 0) {
        q[count++] = p[2];
    }
    int m = a[1] / 2;
    while (m-- > 0) {
        q[count++] = 9;
    }

    m = a[0] / 3;
    while (m-- > 0) {
        q[count++] = 8;
    }
    int x = a[1] % 2;
    int y = a[0] % 3;
    if (x == 0) {
        if (y > 0) {
            q[count++] = (y == 1 ? 2 : 4);
        }
    } else {
        if (y > 0) {
            q[count++] = 6;
            if (y > 1) {
                q[count++] = 2;
            }
        }
    }
    qsort(q, count, sizeof(q[0]), cmp);
    long long num = 0;
    for (int i = 0; i < count; i++) {
#ifndef ONLINE_JUDGE
        printf("%d ", q[i]);
#endif
        num = num * 10 + q[i];
    }
#ifndef ONLINE_JUDGE
    printf("\n");
#endif
    printf("%lld\n", num);
    return 0;
}
