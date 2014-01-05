#include <stdio.h>
#include <math.h>

static int gcd(int m, int n) {
    if (m < n) {
        int t = m;
        m = n;
        n = t;
    }
    while (n != 0) {
        int r = m % n;
        m = n;
        n = r;
    }

    return m;
}

/*
 * This method takes 3 loops to find it.
 */
/*
 * The basic idea is that:
 * a = m^2-n^2;
 * b = 2*m*n
 * c = m^2 + n^2
 * where m > n > 1, and gcd(m,n) = 1, one of m and n is even.
 * So a + b +c  = 2*m(m+n)*d, where d is a common divisor of a,b and c.
 * One of m and n is even, so m + n must be odd.
 * a + b + c = 2*m(m+n)*d = s
 * let k = m+n
 * m, and k are divisors of s/2, and k is odd and gcd(k,m) = 1.
 * Thus, iterate divisors of s/2, and test m, and k with above conditions.
 */
static int find_pythagorean(int s) {
    int loops = 0;
    int s2 = s / 2;
    int mlimit = ceil(sqrt(s2)) - 1;
    int m = 0;
    for (m = 2; m <= mlimit; m++) {
        if (s2 % m == 0) {
            int sm = s2 / m;
            while ((sm & 0x01) == 0) {
                loops++;
                sm /= 2;
            }
            int k = m + 2;
            /*
             * Here is a language gap, == has higher precendence than &, so if there is no
             * parathensis, it will become m & (0x01 == 0), because == has high precendence
             * which is not ideal effect.
             * So, m & 0x01 == 0 ----> equals to m & 0, which is 0, so this if block never
             * gets executed.
             * By adding parathensis (a & 0x01) == 0 is testing for even and odd
             */
            if ((m & 0x01) == 0) {
                k = m + 1;
            }
            while (k < 2*m && k <= sm) {
                loops++;
                if (sm % k == 0 && gcd(k, m) == 1) {
                    int d = s2 / (k*m);
                    int n = k - m;
                    int a = d * (m*m - n*n);
                    int b = 2 * m * n * d;
                    int c = d * (m*m + n*n);
                    printf(" %d + %d + %d = %d, %d + %d=%d\n", a, b, c, s, a*a, b*b, c*c);
                    printf("loops for advanced methods is %d\n", loops);
                    return a * b * c;
                }
                k += 2;
            }
        }
    }
    printf("loops for advanced methods is %d\n", loops);
    return -1;
}

/*
 * After some compute, we get following truth:
 *    350 < c < 1000
 *    1 < a < 325
 *    325 < b < 649
 *    a+b < 650
 * by:
 * (a+b+c)^2 = 1000*1000 --> a^2+b^2+c^2+2ab+2ac+2bc=1000*1000
 * Given the truth: a < b < c, a,b,c are natural number, and
 * a^2+b^2=c^2
 * a^2+b^2+c^2+2ab+2ac+2bc=1000*1000 < c^2 + c^2 + 2c^2 + 2c^2 +2c^2 = 8c^2
 * so 8c^2 > 1000*1000
 * c > 250*sqrt(2) = 350
 * so c > 350, given a+b+c=1000, so  350 < c < 1000
 * a + b < 650, and a < b, so
 * 1 < a < 325
 * 325 < b < 649
 * Then enumerate a, b and c and find their product. loops 41811976
 *
 * In fact, we only have to enumerate a and b, for c we can use c = 1000-a-b
 * this improve from 41811976 to 64327.
 *
 * Notice, b < c, c = 1000 -a -b, so
 * b < 1000 - a - b, so we get b < 500 - a/2, this reduce loops from 64327 to  24776.
 */
int main(void) {
    int a, b, c;
    int loops = 0;
    for (a = 1; a < 325; a++) {
        int lb = 500 - a/2;
        for (b = 326; b < lb; b++) {
            //for (c = 350; c < 1000; c++) {
            c = 1000 - a - b;
                loops++;
                //if ((a + b + c) != 1000) {
                    //continue;
                //}
                if (!(a < b && b < c)) {
                    continue;
                }
                if (a*a + b*b == c*c) {
                    printf(" got it a=%d, b=%d, c=%d, %d + %d = %d\n", a, b, c, a*a, b*b, c*c);
                    printf(" product is %d\n", (a*b*c));
                    goto done;
                }
            //}
        }
    }
done:
    printf(" using loops %d\n", loops);
    printf(" no try some new methods\n");
    printf("find sum is 1000 pythagorean is %d\n", find_pythagorean(1000));
    return 0;
}
