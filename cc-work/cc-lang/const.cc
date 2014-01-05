#include <iostream>
using namespace std;

class Const {
public:
    static void const_ptr();
};

void Const::const_ptr() {
    const char *p = NULL;
    char a = 'a';
    p = &a;
    // compile error, *p is read-only
    //*p = 'b';
    cout << *p << endl;
    char const *p0 = NULL;
    p0 = &a;
    //*p0 = 'c';
    cout << *p0 << endl;
    char * const p1 = &a;
    char b = 'b';
    // compile error p1 is read-only
    //p1 = &b;
    // but *p1 is changable
    *p1 = 'd';
    cout << *p1 << endl;
    char w[5];
    const char *z = w;
    z[0] = 'h';
    z[1] = 'e';
    z[2] = 'l';
    z[3] = 'l';
    z[4] = 'o';
    z[5] = '\0';
    cout << z << endl;
}

int main(int argc, char **argv) {
    Const::const_ptr();

    return 0;
}
