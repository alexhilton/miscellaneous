#include <stdio.h>

int main() {
    int n;
    long long sum = 0;
    while (scanf("%d", &n) != EOF) {
        if (n == 0 || n == 1) {
            printf("1\n");
            continue;
        }
        if (n == -1) {
            printf("0\n");
            continue;
        }
        int sign = n < 0;
        if (sign) {
            n *= -1;
        }
        sum = n * (n + 1) / 2;
        if (sign) {
            sum--;
            sum *= -1;
        }
        printf("%lld\n", sum);
    }

    return 0;
}
