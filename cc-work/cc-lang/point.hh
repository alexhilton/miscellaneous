#ifndef __POINT_HH
#define __POINT_HH
#include <iostream>
using namespace std;

class Point {
private:
    int x;
    int y;
public:
    Point();
    Point(int x0, int y0);
    Point(const Point &p);
    Point &operator = (const Point &p);
    bool operator == (const Point &p) const;
    Point operator + (const Point &p) const;
    friend ostream & operator << (ostream &o, const Point &p);
};

#endif
