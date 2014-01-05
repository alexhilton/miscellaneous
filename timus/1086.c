#include <stdio.h>
#include <math.h>

int isPrime(int n) {
    if ((n & 0x01) == 0) {
        return 0;
    }
    int limit = floor(sqrt(n));
    for (int i = 2; i <= limit; i++) {
        if (n % i == 0) {
            return 0;
        }
    }

    return 1;
}

int main() {
    int a[15000];
    a[0] = 0;
    a[1] = 2;
    a[2] = 3;
    a[3] = 5;
    a[4] = 7;
    a[5] = 11;
    int n = 13;
    for (int i = 6; i <= 15000; i++) {
        while (!isPrime(n)) {
            n += 2;
        }
        a[i] = n;
        n += 2;
    }
#ifndef ONLINE_JUDGE
    for (int i = 0; i < 21; i++) {
        printf(" %d", a[i]);
    }
    printf(" %d ", a[15000]);
    printf("\n");
#endif

    int x = 0;
    scanf("%d", &x);
    for (int i = 0; i < x; i++) {
        int k;
        scanf("%d", &k);
        printf("%d\n", a[k]);
    }

    return 0;
}
