#include <stdio.h>
#include <math.h>

/*
 * 0 1
 * 1 10
 * 2 100
 * 3 1000
 * 4 10000
 * so, in the sequence, m = n(n+1)/2 + 1, where n=[0, x], the m'th is 1, all others are 0.
 * Given k, if k == m then a[k] is 1, otherwise 0, so it becomes:
 * k = n(n+1) / 2, if there are any n [0, x], then a[k] is 1, or no such n, a[k] 0.
 * n^2 + n - q = 0, where q = 2(k-1)
 * if there are any integer n, then a[k] is 1, otherwise, a[k]=0.
 * n = (sqrt(1+4q)-1) / 2.
 * to make n integral, we must make sqrt(1+4q) an odd integral number.
 * So, 1+4q must be perfect square and odd, apparent it is odd, so
 * if 1+4q, where q=2(k-1), is a perfect square, a[k] is 1
 * or, if 8k-7 is a perfect square, a[k] is 1, otherwise 0.
 */
int main() {
    int count;
    int k;
    scanf("%d", &count);
    for (int i = 0; i < count; i++) {
        scanf("%d", &k);
        double y = (double) 8 * (double) k - 7;
        double x = sqrt(y);
        printf("%d ", (floor(x) == ceil(x)));
    }

    return 0;
}
