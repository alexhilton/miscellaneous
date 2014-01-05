#include <stdio.h>
#include <math.h>

/*
 * Our initial solution does not require any codes, but can only solve that problem.
 * Here is it:
 * The problem is least divisible by all numbers from [1, 20], that means to find the
 * Least Common Multiple of [1 to 20].
 * So, LCM of [1,10] is 2520
 * Then for LCM[1, 20] = LCM[2520, [11, 20]]
 * 11, 13, 17, 19 are primes, so r = lcm[11*13*17*19, lcm[2520, 12,14,15,16,18,20]
 * for them, only 16 is not divisible by 2520, so the result is 
 * 11*13*17*19*2520*2 = 232792560.
 */

static int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
/*
 * But for a general number k, how to find N which N is LCM of [1, k].
 * If all numbers between 1 and k are primes, then N will be 2*3*4*...k, if all are primes.
 * But not that simple.
 * The insight is that if N is a lcm, it must be a products of a list of primes.
 * 2 = 1, 2 = 1*2 = 2
 * 3 = 1, 2, 3= 2 * 3 = 6
 * 4 = 1,2,3,4=2*3*2 = 12 = 2^2*3
 * 5 = 1,2,3,4,5=2*3*2*5=60 = 2^2*3*5
 * 6 = 1,2,3,4,5,6=2*3*2*5=60 = 2^2*3*5
 * So, define N is the lcm of [1,k], p is a list of primes, a is exponents of primes:
 * N = p[1]^a[1]*p[2]^a[2]*...p[i]^a[i]; where p[i] <= k,p[i]^a[i] <= k.
 * For each p[i], the exponent is a[i] and p[i]^a[i] <= k, so a[i] = floor(log(k)/log(p[i]).
 * we need prime list p[i] where p[i] <= k
 */
static int lcm_up_to(int k) {
    int i = 0;
    /*
     * Here, since for each prime factor needs to find its exponent
     * which is natural number and initial value is 1, so if p[i]^2 > k,
     * then its exponent a[i] could only be 1. which means for p[i] > sqrt(k),
     * its exponent is 1 and no need to compute.
     */
    int limit = floor(sqrt(k));
    int n = 1;
    while (primes[i] <= k) {
        int a = 1; // orginal exponent of p[i]
        if (primes[i] <= limit) {
            a = floor(log(k) / log(primes[i]));
        }
        if (a == 1) {
            n *= primes[i];
        } else {
            n *= ((int) pow(primes[i], a));
        }
        i++;
    }
    return n;
}

int main(void) {
    int i = 0;
    for (i = 2; i <= 20; i++) {
        printf("lcm up to %2d is %-10d\n", i, lcm_up_to(i));
    }
    return 0;
}
