/*
 * This problem is to test your understanding of recursion.
 * Find the right recursion function and everything is fine.
 * Just remember not to store the values.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void funca(int i, int n) {
    if (i < n) {
        char sign = (i & 0x01) == 0 ? '+' : '-';
        printf("sin(%d%c", i, sign);
        funca(i+1, n);
        printf(")");
    } else {
        printf("sin(%d)", n);
    }
}

int funcs(int i, int n) {
    if (i <= 1) {
        funca(1, 1);
        return 1;
    } else {
        printf("(");
        
        int d = funcs(i-1, n) + (n-i+1);
        printf("+%d)", d);
        funca(1, i);
        return 1;
    }
}

int main(void) {
    int n;
    scanf("%d", &n);
    funcs(n, n);
    printf("+1\n");
    return 0;
}
