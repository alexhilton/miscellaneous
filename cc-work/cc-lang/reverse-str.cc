#include <iostream>
#include <cstring>

using namespace std;

class String {
public:
    static void reverse(char *str);
    static inline void swap(char &a, char &b);
    static char *bare_reverse(char *str);
};

void String::reverse(char *str) {
    const int len = strlen(str) - 1;
    const int center = len / 2;
    for (int i = 0; i <= center; i++) {
        //char tmp = str[len - i];
        //str[len - i] = str[i];
        //str[i] = tmp;
        swap(str[i], str[len - i]);
    }
}

void String::swap(char &a, char &b) {
    char tmp = b;
    b = a;
    a = tmp;
}

char* String::bare_reverse(char *str) {
    char *p = str;
    while (*p != '\0') {
        p++;
    }
    p--;
    char *q = str;
    while (q < p) {
        char t = *p;
        *p = *q;
        *q = t;
        q++;
        p--;
    }
    return str;
}

int main(int argc, char **argv) {
    const size_t limit = 64;
    char *str = new char[limit];
    cin.getline(str, limit);
    String::reverse(str);
    cout << str << endl;

    cout << "try bare reverse" << endl;
    cout << String::bare_reverse(str) << endl;
    delete str;
    return 0;
}
