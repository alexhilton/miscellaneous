/*
 * Brute-Force method:
 * List all combination of input array, sum each combination and find least diffrerence.
 * Complexity is O(2^n*n).
 * If input size increase, this method cannot fit, though can cut some branch.
 */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    long a[20];
    int size;
    long sum = 0;
    scanf("%d", &size);
    for (int i = 0; i < size; i++) {
        scanf("%ld", &a[i]);
        sum += a[i];
    }
    if (size == 1) {
        printf("%ld\n", a[0]);
        return 0;
    }
    if (size == 2) {
        printf("%ld\n", (long) abs(a[0] - a[1]));
        return 0;
    }
    long part_sum = sum;
    long least_diff = sum;
    for (int i = 0; i < (1 << size) - 1; i++) {
        part_sum = 0;
        for (int k = 0; k < size; k++) {
            if ((i >> k) & 0x01) {
                part_sum += a[k];
            }
        }
        long t = abs(2*part_sum - sum);
        if (least_diff > t) {
            least_diff = t;
        }
    }
    printf("%ld\n", least_diff);
    return 0;
}
