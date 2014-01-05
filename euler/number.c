#include <math.h>
#include "number.h"

int is_even(int n) {
    return (n & 0x01) == 0;
}

int gcd(int n, int m) {
    if (n > m) {
        int t = n;
        n = m;
        m = t;
    }
    while (n != 0) {
        int r = m % n;
        m = n;
        n = r;
    }
    return m;
}

int lcm(int n, int m) {
    return m*n / gcd(n, m);
}

int is_prime(int n) {
    if (n <= 1) {
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
    const int limit = floor(sqrt(n));
    int f = 5;
    while (f <= limit) {
        if (n % f == 0) {
            return 0;
        }
        if (n % (f+2) == 0) {
            return 0;
        }
        f += 6;
    }

    return 1;
}
