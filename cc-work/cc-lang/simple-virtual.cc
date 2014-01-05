#include <iostream>
using namespace std;

class Base {
public:
    virtual void print();
};

class Derived : public Base {
public:
    void print();
};

void Base::print() {
    cout << "from base, for base" << endl;
}

void Derived::print() {
    cout << "for derived" << endl;
}

int main() {
    Derived d;
    Base &b = d;
    b.print();
    Base *b1 = &d;
    b1->print();
    return 0;
}
