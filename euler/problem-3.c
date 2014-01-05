/*
 * This is the brute force method:
 * from sqrt(x) to 1, for each odd, if it is a factor and it is a prime, we got it.
 * Above method is lucky enough to get the right answer for the given number. But it is buggy.
 * Because the factor of a number is not alway less than sqrt(n), like 3 of 6, 7 of 35 or 13 of 39.etc.
 * So, this method will fail for some numbers.
 * Besides, this algorithms is O(n^2).
 */
#include <stdio.h>
#include <math.h>

static int is_prime(int n) {
    int x = floor(sqrt(n));
    int i = 2;
    for (i = 2; i <= x; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

/*
 * A non-prime number can be defined as:
 *    n = f1^x * f2^y * f3^z ...; which f1,f2,f3 are prime factors
 * The worst of this algorithm is o(n)
 */
static int find_biggest_prime_factor(long n) {
    /*
     * Deal the even number first.
     * a even number n = 2^x * f1 * f2...;
     * After get rid of 2^x, the biggest prime factor of n div 2^x is the same to n.
     */
    int lastFactor = 1;;
    if ((n & 0x01) == 0) {
        n /= 2;
        lastFactor = 2;
        while ((n & 0x01) == 0) {
            n /= 2;
        }
    }
    /*
     * factor can be bigger than sqrt(n), but we should only worry about factors less than sqrt(n),
     * because n div factor(less than sqrt(n)) gives another factor (larger than sqrt(n)). As a result,
     * we check odds from 3 up to sqrt(n).
     */
    int factor = 3;
    int limit = floor(sqrt(n));
    // after each loop, n becomes a factor of its original value
    while (n > 1 && factor < limit) {
        if (n % factor == 0) {
            n /= factor;
            lastFactor = factor;
            while (n % factor == 0) {
                n /= factor;
            }
            limit = floor(sqrt(n));
        }
        factor += 2;
    }

    if (n == 1) {
        printf("biggest prime factor is %d\n", lastFactor);
        return lastFactor;
    } else {
        // so n is also a prime
        printf("biggest prime factor is %d\n", n);
        return n;
    }
}

int main(void) {
    long n = 600851475143L;
    int x = floor(sqrt(n));
    if ((x & 0x01) == 0) {
        x--;
    }
    while (x >= 1) {
        if (n % x == 0) {
            if (is_prime(x)) {
                printf(" it is %d\n", x);
                break;
            }
        }
        x -= 2;
    }

    int bpf = find_biggest_prime_factor(n);
    printf("biggest prime factor of %ld is %d\n", n, bpf);
    return 0;
}
