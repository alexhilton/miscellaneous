#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * Brute force is about 10^8
 *
 * While seive method is about 10^7.
 */
static long loops = 0;

/*
 * Cannot use int, will overflow.
 * Even with improve prime test method, loops is 29726425
 */
static int is_prime(int n) {
    if (n == 1) {
        return 0;
    }
    if (n < 4) {
        return 1;
    }
    if ((n & 0x01) == 0) {
        return 0;
    }
    if (n < 9) {
        return 1;
    }
    if (n % 3 == 0) {
        return 0;
    }
    int limit = floor(sqrt(n));
    int f = 5;
    while (f <= limit) {
        loops++;
        if (n % f == 0) {
            return 0;
        }
        if ((n % (f+2)) == 0) {
            return 0;
        }
        f += 6;
    }

    return 1;
}

static long sum_primes_under(int n) {
    long s = 2;
    int i = 3;
    for (i = 3; i <=n; i += 2) {
        if (is_prime(i)) {
            s += i;
        }
    }

    return s;
}

static long sum_primes_under_with_seive(int l);
static long sum_primes_under_with_seive2(int l);

int main(void) {
    int i;
    for (i = 2; i <= 10; i++) {
        printf(" sum of primes under %2d is %d\n", i, sum_primes_under(i));
    }

    int l = 2000000;
    long prime = sum_primes_under(l);
    printf("sum of primes under %d is %ld, with loops %ld\n", l, prime, loops);
    printf(" try advanced method Seive of Erath.....:\n");
    printf("primitive seive method %ld\n", sum_primes_under_with_seive(l));
    printf("better seive method %ld\n", sum_primes_under_with_seive2(l));
    return 0;
}

/*
 * Seive of Eratosthenes.
 * list all number upto l:
 * cross multiples of next prime p, p = { 2, 3 ....}
 */
static long sum_primes_under_with_seive(int l) {
    int loops = 0;
    // index stand for number [1, l]
    int *seive = (int *) calloc(l+1, sizeof(int));
    seive[0] = 1; // 1
    seive[1] = 1; // 2
    seive[2] = 0; // 3
    seive[3] = 0; // 3
    int i = 2;
    // cross out every even number
    for (i = 4; i < l; i += 2) {
        loops++;
        seive[i] = 1;
    }
    const int limit = floor(sqrt(l));
    // starting from 3, every prime is odd
    for (i = 3; i <= limit; i += 2) {
        if (!seive[i]) {
            // for each prime, cross its multiples out
            int m;
            for (m = i*i; m <= l; m += 2*i) {
                loops++;
                seive[m] = 1;
            }
        }
    }
    long s = 0;
    for (i = 1; i <= l; i++) {
        loops++;
        if (!seive[i]) {
            s += i;
        }
    }
    free(seive);
    printf("primitive seive method needs %d loops\n", loops);
    return s;
}

/*
 * Even numbers do not need to concern. All about odd number.
 * again, concern numbers starting from 3.
 * Odd number is 2*i+1, where i is its order in sequence, like
 * 3, 5, 7, 9 .... 2*i+1
 * 1, 2, 3, 4 ....  i
 * So, if p = 2*i+1, which is a prime, then
 * p^2 = (2*i+1)^2 = 2*[2i(i+1)]+1, whose index is 2i(i+1).
 */
long sum_primes_under_with_seive2(int l) {
    int loops = 0;
    int seive_bound = (l - 1) / 2;
    int *seive = (int *) calloc(seive_bound+1, sizeof(int));
    const int cross_limit = (floor(sqrt(l)) - 1) / 2;
    int i = 1;
    for (i = 1; i <= cross_limit; i++) {
        if (!seive[i]) {
            int j;
            for (j = 2*i*(i+1); j <= seive_bound; j += 2*i+1) {
                loops++;
                seive[j] = 1;
            }
        }
    }
    long s = 2;
    for (i = 1; i <= seive_bound; i++) {
        if (!seive[i]) {
            s += 2*i + 1;
        }
    }

    printf(" better seive method takes %d loops\n", loops);
    free(seive);
    return s;
}
