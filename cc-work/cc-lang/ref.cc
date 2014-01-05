#include <iostream>
using namespace std;

class Ref {
public:
    static void ref();
};

void Ref::ref() {
    int a = 5;
    int &b = a;
    b = 4;
    int c = 6;
    &b = c;
    cout << b << endl;
}

int main(int argc, char **argv) {
    Ref::ref();
    return 0;
}
