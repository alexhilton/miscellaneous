#include <stdio.h>
#include <math.h>

/*
 * No better way, just find nth prime.
 * Only way to improve is the is_prime function.
 */
static int is_prime(int n) {
    const int limit = floor(sqrt(n));
    int i;
    for (i = 2; i <= limit; i++) {
        if (n % i == 0) {
            return 0;
        }
    }

    return 1;
}

int find_nst_prime(int n) {
    if (n <= 1) {
        return 2;
    }
    int i = 2; // i th
    int k = 3; // number
    while (1) {
        if (is_prime(k)) {
            if (i >= n) {
                break;
            }
            i++;
        }
        k += 2;
    }

    return k;
}

int main(void) {
    int i = 1;
    for (i = 1; i < 10; i++) {
        printf("%2d th prime is %d\n", i, find_nst_prime(i));
    }
    printf("10001 st prime is %d\n", find_nst_prime(10001));
    return 0;
}
