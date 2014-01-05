#include <stdio.h>
#include <string.h>

typedef struct Point Point;

struct Point {
    int x;
    int y;
    char ch;
    double z;
    char name[63];
};

int main() {
    Point p;
    p.x = 3;
    p.y = 4;
    p.ch = 'a';
    p.z = 3.1415926f;
    strcpy(p.name, "Hello, world");
    int *pobject = (int *) &p;
    printf("%d, %d\n", *pobject, *(pobject+1));
    printf("%c, %g\n", *(pobject+2), (double) (*(pobject+3)));
    printf("%s\n", (char *) (pobject+4));

    return 0;
}
