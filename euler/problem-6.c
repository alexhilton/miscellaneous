#include <stdio.h>

/*
 * Key formula of this problem:
 * 1 + 2^2 + 3^2 + ... + n^2 = n(n+1)(2n+1)/6
 * 1+2+3+...+n = n(n+1)/2
 * So, Sn^2 - S^2n is
 * [n(n+1)/2]^2 - n(n+1)(2n+1)/6 = n(n+1)(n-1)(3n+2)/12
 */
int main(void) {
    int n = 100;
    int r = n * (n + 1) * (n - 1) * (3*n + 2) / 12;
    printf("100's is %d\n", r);
    n = 10;
    r = n * (n + 1) * (n - 1) * (3*n + 2) / 12;
    printf("10's is %d\n", r);
    return 0;
}
