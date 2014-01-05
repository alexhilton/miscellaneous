#include <iostream>
using namespace std;

class Base {
public:
    virtual void f() {
        cout << "Base::f" << endl;
    }

    virtual void g() {
        cout << "Base::g" << endl;
    }

    virtual void h() {
        cout << "Base::g" << endl;
    }
};

typedef void (*func)(void);

int main() {
    Base b;

    int *virtual_table = (int *) &b;
    int *first_func = (int *) *virtual_table;
    cout << "virtual table address: " << virtual_table << endl;
    cout << "virtual table - first function address: " << first_func << endl;
    func pfuncf = NULL;
    func pfuncg = NULL;
    func pfunch = NULL;
    pfuncf = (func) *first_func;
    pfuncf();
    /*func pfuncg = (func) *(first_func + 1);
    pfuncg();
    func pfunch = (func) *(first_func + 2);
    pfunch();*/

    pfuncf = (func) *((int *)*(int *)(&b));
    pfuncf();
    pfuncg = (func) *((int *)*(int *)(&b)+1);
    pfuncg();
    pfunch = (func) *((int *)*(int *)(&b)+2);
    pfunch();

    return 0;
}
