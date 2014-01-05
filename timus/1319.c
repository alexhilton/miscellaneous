#include <stdio.h>

/*
 * The iterate order is a little bit dizzy.
 * calculate them manually and slowly, then it is okay.
 */
int main() {
    int n;
    int a[100][100];
    scanf("%d", &n);
    int x = 1;
    for (int c = n-1; c >= 0; c--) {
        for (int r = 0; c+r < n && r < n; r++) {
            a[r][r+c] = x++;
        }
    }
    for (int r = 1; r < n; r++) {
        for (int c = 0; r+c < n && c < n-r; c++) {
            a[r+c][c] = x++;
        }
    }
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            printf("%d ", a[r][c]);
        }
        printf("\n");
    }

    return 0;
}
