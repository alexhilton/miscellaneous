/*
 * AC.
 * But i failed to figure out any difference with previous one.
 * But this solution is more elegant.
 */
#include <stdio.h>
#include <string.h>

int main() {
    int n;
    char str[21];
    scanf("%d %s", &n, str);
    int k = strlen(str);
#ifndef ONLINE_JUDGE
    printf("n is %d, k is %d\n", n, k);
#endif
    /*
     * The insight is that,
     * n !!!! = n*(n-k)*(n-2k)*(n-3k)....(n-xk), you know, n%k = n-xk, where x=n/k, next term n-(x+1)k < 0
     * n !!!! = n*(n-k)*(n-2k)*(n-3k)....k*0, n%k = 0,
     * so, term is the same:
     * for i=[n, 0):
     *   r *= i;
     */
    int result = 1;
    for (int i = n; i > 0; i -= k) {
        result *= i;
    }
    printf("%d\n", result);
    return 0;
}
