#include <iostream>
#include "point.hh"

Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(int x0, int y0) {
    x = x0;
    y = y0;
}

Point::Point(const Point &p) {
    x = p.x;
    y = p.y;
}

Point & Point::operator = (const Point &p) {
    if (this == &p) {
        return *this;
    }
    x = p.x;
    y = p.y;
    return *this;
}

bool Point::operator == (const Point &p) const {
    return x == p.x && y == p.y;
}

Point Point::operator + (const Point &p) const {
    return Point(x + p.x, y + p.y);
}

ostream & operator << (ostream &o, const Point &p) {
    o << "(" << p.x << ", " << p.y << ")";
    return o;
}

int main(void) {
    Point a(1, 2);
    Point b(4, 5);
    Point c(3, 2);
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    cout << "a == b ?" << (a == b) << endl;
    cout << "a + b = " << (a + b) << endl;
    c = b;
    cout << "c = b " << c << endl;
    cout << "b == c " << (b == c) << endl;
    return 0;
}
