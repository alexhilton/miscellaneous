/*
 * Description:
 * This problem is simple even with brute force.
 * The key is to find a formula to calculate each number.
 * So, for number limit n, the sum of multiples of i, is [1, ... k] * i, where i*k < n;
 * But for two numbers i and j, the multiples of both are summed twice, so we have to substract
 * sum of multiples of LCM of i and j.
 */
#include <stdio.h>

static int find_sum(int n, int i, int j);
static find_gcd(int i, int j);
static find_lcm(int i, int j);

int main(int argc, char *argv[]) {
    int a = find_sum(10, 3, 5);
    printf(" 10, 3,5 is %d, expected 23\n", a);
    printf(" 11, 3, 5 is %d, expected 33\n", find_sum(11, 3, 5));
    printf(" 11, 3, 5 is %d, expected 33\n", find_sum(12, 3, 5));
    printf(" 11, 3, 5 is %d, expected 45\n", find_sum(13, 3, 5));
    printf("1000, 3, 5 is %d\n", find_sum(1000, 3, 5));
    return 0;
}

int find_sum(int n, int i, int j) {
    int ki = (n - 1) / i;
    int kj = (n - 1) / j;
    int si = (ki + ki * (ki - 1) / 2) * i;
    int sj = (kj + kj * (kj - 1) / 2) * j;
    int lcm = find_lcm(i, j);
    int klcm = (n - 1) / lcm;
    int slcm = (klcm + klcm * (klcm - 1) / 2) * lcm;
    return si + sj - slcm;
}

int find_lcm(int i, int j) {
    return i * j / find_gcd(i, j);
}

int find_gcd(int i, int j) {
    if (i < j) {
        int t = j;
        j = i;
        i = t;
    }
    while (j != 0) {
        int r = i % j;
        i = j;
        j = r;
    }
    return i;
}
