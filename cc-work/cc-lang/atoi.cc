#include <iostream>

using namespace std;

class Atoi {
public:
    static int atoi(const char *str);
};

int Atoi::atoi(const char *str) {
    int ret = 0;
    int sign = 1;
    const char *p = str;
    if (*p == '-') {
        sign = -1;
        p++;
    } else if (*p == '+') {
        p++;
    }
    while (*p != '\0') {
        int i = (int) (*p - '0');
        ret = ret * 10 + i;
        p++;
    }
    return ret * sign;
}

int main(void) {
    cout << Atoi::atoi("1234") << endl;
    cout << Atoi::atoi("-1234") << endl;
    cout << Atoi::atoi("+1234") << endl;
    return 0;
}
