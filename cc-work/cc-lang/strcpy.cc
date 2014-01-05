#include <iostream>

using namespace std;

class Strcpy {
public:
    static void strcpy(char *dest, const char *src);
    static int strlen(const char *str);
};

void Strcpy::strcpy(char *dst, const char *src) {
    while ((*dst++ = *src++) != '\0')
        ;
}

int Strcpy::strlen(const char *str) {
    int len = 0;
    while (*str++ != '\0') {
        len++;
    }
    return len;
}

int main(int argc, char **argv) {
    char c[] = "free dom";
    char a[5];
    char *d = "is nothing";
    Strcpy::strcpy(a, "hello");
    cout << a << endl;
    cout << a << " length of is " << Strcpy::strlen(a) << " sizeof " << sizeof(a) << endl;
    char b[] = "shit";
    cout << b << " length of is " << Strcpy::strlen(b) << " sizeof " << sizeof(b) << endl;
    cout << "size of int " << sizeof(int)  << " size of char * " << sizeof(char *) << endl;
    cout << "size of int * " << sizeof(int *) << endl;
    return 0;
}
