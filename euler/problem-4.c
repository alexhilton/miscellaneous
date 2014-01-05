/*
 * Use brute force method.
 * for each i in [999~101]
 *    for each j = [i, 101]
 *       p = i * j;
 *       if p is palindrome, done
 * O(n^2)
 * It is 906609 = 993 * 913.
 * After improvement, it takes 7013 loops.
 * But after analyzing and with divisible 11, it takes 1328 loops, save a lot of time, dramatically improvement.
 */
#include <stdio.h>

static int is_palindrome(int n) {
    int digits[10];
    int i = 0;
    while (n != 0) {
        digits[i++] = n % 10;
        n /= 10;
    }
    int j = 0;
    for (j = 0; j < i/2; j++) {
        if (digits[j] != digits[i-j-1]) {
            return 0;
        }
    }
    return 1;
}

/*
 * We can do better than that by finding the following truth:
 * P = 100000*x + 10000*y + 1000*z + 100*z + 10*y + x;
 * p = 100001*x + 10010*y + 1100*z;
 * p = 11(9091x+910y+100z);
 * so, P must be divisible by 11, and so if P =a*b, a or must be divisible by 11 too.
 * So, we only need to check (i, j) = [100, 999], where (i%11== 0 or j%11 == 0), loops
 * reduce dramatically by adding such a condition.
 */
static int find_biggest() {
    int loops = 0;
    int biggest = 0;
    int n1 = 0, n2 = 0;
    int a = 999;
    int b = 0;
    int db = 0;
    while (a >= 100) {
        if (a % 11 == 0) { // if a is divisible by 11, then check every b in [999,100]
            b = 999;
            db = 1;
        } else {
            b = 990; // if a is not, b MUST be divisible by 11, check every b in [999, 100], which b % 11 == 0
            db = 11; // that is, 990, 979, 968 ... 110
        }
        while (b >= a) {
            loops++;
            int p = a * b;
            if (p < biggest) {
                break;
            }
            if (is_palindrome(p)) {
                biggest = p;
                n1 = a;
                n2 = b;
                break; // following palidrome must be less
            }
            b -= db;
        }
        a--;
    }

    printf("find_biggest is %d=%d * %d, with loops %d\n", biggest, n1, n2, loops);
    return biggest;
}

int main(void) {
    int i;
    int n1 = 999;
    int n2 = 101;
    if (is_palindrome(n1)) {
        printf("999 is palindrome\n");
    } else {
        printf("999 is not palindrome, soemthing wrong\n");
        return 0;
    }
    if (is_palindrome(n2)) {
        printf("101 is palindrome\n");
    } else {
        printf("999 is not parline, soem\n");
        return 0;
    }
    int loops = 0;
    int big = 0;
    int p1 = 0, p2 = 0;
    for (i = n1; i >= n2; i--) {
        int j = n1;
        for (j = i; j >= n2; j--) {
            loops++;
            int p = i * j;
            // improve: we find a bigger one than big, so if p is less than big
            // we should move to next loop regardless of p is palindrome or not.
            // Because we gonna find biggest palindrome
            if (p < big) {
                break;
            }
            if (is_palindrome(p)) {
                if (big < p) {
                    big = p;
                    p1 = i;
                    p2 = j;
                    printf(" it is %d = %d * %d\n", p, i, j);
                }
                // Here, even i is a big number, but j might not when their product is palindrome.
                // there might be a little smaller i with bigger j whose product is bigger. So here
                // cannot stop whole loops.
                // for example, first loop got 580085 = 995 * 583, which i is 995 and j is 583.
                // but second loop we got 906609 = 993 * 913, which i is 993 and j is 913.
                break;
            }
        }
    }
    printf("biggest is %d = %d * %d, with %d loops\n", big, p1, p2, loops);
    find_biggest();
    return 0;
}
