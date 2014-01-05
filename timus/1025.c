#include <stdio.h>
#include <stdlib.h>

/*
 * sum half of first half.
 * To minimal, just sort ascending.
 */
int cmp_int(const void *a1, const void *a2) {
    return *(int *)a1 - *(int *)a2;
}

int main(void) {
    int n;
    int a[101];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    qsort(a, n, sizeof(int), cmp_int);
    int count = 0;
    for (int i = 0; i < n/2+1; i++) {
        count += a[i] / 2 + 1;
    }
    printf("%d\n", count);

    return 0;
}
