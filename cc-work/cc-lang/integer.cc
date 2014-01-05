#include <iostream>
#include "integer.hh"

Integer::Integer(const Integer &a) {
    value = a.value;
}

Integer::operator int () const {
    return value;
}

Integer & Integer::operator = (const Integer &a) {
    if (this == &a) {
        return *this;
    }
    value = a.value;
    return *this;
}

Integer Integer::operator << (const int offset) const {
    return Integer(value << offset);
}

Integer & Integer::operator <<= (const int offset) {
    value <<= offset;
    return *this;
}

Integer Integer::operator >> (const int offset) const {
    return Integer(value >> offset);
}

Integer & Integer::operator >>= (const int offset) {
    value >>= offset;
    return *this;
}

ostream & operator << (ostream &o, const Integer &a) {
    o << a.value;
    return o;
}

istream & operator >> (istream &i, Integer &a) {
    i >> a.value;
    return i;
}

int main(void) {
    int a = 3;
    Integer b = (Integer) a;
    cout << "b = " << b << endl;
    Integer c = Integer(5);
    cout << " c =  " << c << endl;
    cout << "inpu for d ";
    Integer d(0);
    cin >> d;
    cout << "d is " << d << endl;
    Integer e(d);
    cout << " e is " << e << endl;
    int f = b;
    cout << " f is " << f << endl;
    Integer g(1);
    g = c;
    cout << " g is  " << g << endl;
    cout << " d << 3 " << (d << 3) << endl;
    cout << " d >> 3 " << (d >> 3) << endl;
    d <<= 3;
    cout << " d <<= 3 " << d << endl;
    g >>= 3;
    cout << " g >>= 3 " << g << endl;
    return 0;
}
