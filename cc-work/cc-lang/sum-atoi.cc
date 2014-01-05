#include <iostream>

class SumAtoi {
public:
    static int sum(char *str);
};

int SumAtoi::sum(char *str) {
    char *p = str;
    int sum = 0;
    while (*p != '\0') {
        int num = 0;
        int i = 0;
        if (*p >= '0' && *p <= '9') {
            char *q = p;
            while (*q >= '0' && *q <= '9') {
                num = num * 10 + ((int) (*q - '0'));
                q++;
                i++;
            }
        } else {
            i = 1;
            num = 0;
        }
        p += i;
        sum += num;
    }
    return sum;
}


int main(void) {
    char a[] = "p1p2p3p4p5";
    int sa = 15;
    if (SumAtoi::sum(a) != sa) {
        std::cout << "error for " << a << " bad result " << SumAtoi::sum(a) << std::endl;
    }

    return 0;
}
