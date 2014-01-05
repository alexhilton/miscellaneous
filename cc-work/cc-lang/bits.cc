#include <iostream>
#include <bitset>
#include <cstdio>

using namespace std;

class Bits {
public:
    static void operators();
    static void withBitset();
};

void Bits::operators() {
    printf("0x01 << 3 = 0x%0x\n", (0x01 << 3));
    int a = 0x11;
    printf("a  = 0x%0x\n", a);
    printf("~a = 0x%0x\n", ~a);
    a |= (0x01 << 3);
    printf(".. a = 0x%0x\n", a);
    a &= (~(0x01 << 4));
    printf(" .. a = 0x%0x\n", a);
}

void Bits::withBitset() {
    bitset<32> a(0x11);
    bitset<32> b = a;
    printf("a  = 0x%0x\n", a);
    printf("~a = 0x%0x\n", a.flip());
    printf("..a = 0x%0x\n", b.set(3));
    printf(".. a = 0x%0x\n", b.reset(4));
}

int main(void) {
    Bits::operators();
    Bits::withBitset();
    return 0;
}
