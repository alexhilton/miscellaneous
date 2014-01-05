#include <stdio.h>

int main() {
    int a[10000];
    int count;

    scanf("%d", &count);
    for (int i = 0; i < count*count; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            int k = i - j;
            if (k < 0 || k >= count) {
                break;
            }
            printf("%d ", a[k*count + j]);
        }
    }
    for (int i = 1; i < count; i++) {
        for (int j = count-1, col = i; j >= i && col < count; j--, col++) {
            printf("%d ", a[j*count + col]);
        }
    }
    return 0;
}
