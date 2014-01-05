/* reverse root */
#include <stdio.h>
#include <math.h>
#include <ctype.h>

int main() {
    double results[150000];
    char stream[256*1024 + 1];
    const int stream_limit = 256 * 1024;
    int count = 0;
    double num = 0;
    while (scanf("%lf", &num) != EOF) {
        results[count] = sqrt(num);
        count++;
    }

    int i;
    for (i = count - 1; i >= 0; i--) {
        printf("%.4lf\n", results[i]);
    }

    return 0;
}
