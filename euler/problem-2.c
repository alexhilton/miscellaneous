/*
 * This is brute force method.
 * iterate fibonacci up to 4000000, sum the even item, yields 4613732
 * But, we can do better, to avoid test even and save some loops.
 */
#include <stdio.h>

/*
 * Looping 11 times.
 * Saving about 2/3 execution time.
 */
static int sum_even(int limit) {
    int loop_count = 0;
    int f1 = 1;
    int f2 = 2;
    int sum = 0;
    while (f2 < limit) {
        sum += f2;
        loop_count++;
        int t = f1;
        f1 = f2;
        f2 = f1 + t;
        if (f2 >= limit) {
            break;
        }
        t = f1;
        f1 = f2;
        f2 = f1 + t;
        if (f2 >= limit) {
            break;
        }
        t = f1;
        f1 = f2;
        f2 = f1 + t;
    }
    printf("looping %d times\n", loop_count);
    return sum;
}

/*
 * this way looping 30 times
 */
int main(void) {
    int f1 = 1;
    int f2 = 2;
    int f3 = f1 + f2;
    int sum = 2;
    int lc = 0;
    while (f3 < 4000000) {
        lc++;
        if ((f3 & 0x01) == 0) {
            sum += f3;
        }
        f1 = f2;
        f2 = f3;
        f3 = f1 + f2;
    }
    printf("  sum is %d, lc is %d\n", sum, lc);

    printf(" another way is %d\n", sum_even(4000000));
    return 0;
}
