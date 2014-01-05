#ifndef __INTEGER__HH
#define __INTEGER__HH
#include <iostream>
using namespace std;

class Integer {
private:
    int value;
public:
    explicit Integer(int x) { value = x; }
    Integer(const Integer &a);
    Integer & operator = (const Integer &a);
    bool operator ==  (const Integer &a) const;
    Integer operator + (const Integer &a) const;
    Integer & operator += (const Integer &a);
    Integer operator - (const Integer &a) const;
    Integer & operator -= (const Integer &a);
    Integer operator * (const Integer &a) const;
    Integer & operator *= (const Integer &a);
    Integer operator / (const Integer &a) const;
    Integer & operator /= (const Integer &a);
    Integer operator << (const int offset) const;
    Integer & operator <<= (const int offset);
    Integer operator >> (const int offset) const;
    Integer & operator >>= (const int offset);
    Integer & operator ++ ();
    Integer & operator -- ();
    operator int () const;
    friend ostream & operator << (ostream &o, const Integer &a);
    friend istream & operator >> (istream &i, Integer &a);
};

#endif
