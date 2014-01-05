#include <stdio.h>

int main() {
    int i, j;
    char a[3];
    int n;
    scanf("%d", &n);
    while (n--) {
        scanf("%s", a);
        i = a[0] - 'a' + 1;
        j = a[1] - '0';
        int cnt = 0;
        if (i-1 >= 1 && i-1 <= 8 && j+2 >= 1 && j+2 <= 8) {
            cnt++;
        }
        if (i+1 >= 1 && i+1 <= 8 && j+2 >= 1 && j+2 <= 8) {
            cnt++;
        }
        if (i+2 >= 1 && i+2 <= 8 && j+1 >= 1 && j+1 <= 8) {
            cnt++;
        }
        if (i+2 >= 1 && i+2 <= 8 && j-1 >= 1 && j-1 <= 8) {
            cnt++;
        }
        if (i-1 >= 1 && i-1 <= 8 && j-2 >= 1 && j-2 <= 8) {
            cnt++;
        }
        if (i+1 >= 1 && i+1 <= 8 && j-2 >= 1 && j-2 <= 8) {
            cnt++;
        }
        if (i-2 >= 1 && i-2 <= 8 && j+1 >= 1 && j+1 <= 8) {
            cnt++;
        }
        if (i-2 >= 1 && i-2 <= 8 && j-1 >= 1 && j-1 <= 8) {
            cnt++;
        }
        printf("%d\n", cnt);
    }

    return 0;
}
