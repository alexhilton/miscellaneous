#include <iostream>
#include <cstring>

using namespace std;

class String {
public:
    String(char *str = NULL);
    String(const String &another);
    ~String();
    String & operator = (const String &another);
    String operator + (const String &a);
    void print();
    friend ostream& operator << (ostream &, const String &);
    friend istream& operator >> (istream &, String &);
private:
    char *data;
};

String::String(char *str) {
    if (str == NULL) {
        data = new char[1];
        data[0] = '\0';
    } else {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }
}

String::String(const String &another) {
    data = new char[ strlen(another.data) + 1];
    strcpy(data, another.data);
    //String(another.data); will cause segmentation fault
}

String& String::operator = (const String &another) {
    if (this == &another) {
        return *this;
    }

    delete data;
    data = new char[strlen(another.data) + 1];
    strcpy(data, another.data);
    return *this;
}

void String::print() {
    if (data != NULL) {
        cout << data << endl;
    }
}

String::~String() {
    delete data;
}

ostream& operator << (ostream & out, const String &obj) {
    out << obj.data;
    return out;
}

istream& operator >> (istream & in, String &obj) {
    char buf[1024];
    in.getline(buf, 1024);
    obj = String(buf);
    return in;
}

String String::operator + (const String &a) {
    char *tmp = new char[strlen(data) + strlen(a.data) + 1];
    strcpy(tmp, data);
    strcat(tmp, a.data);

    String t(tmp);
    delete tmp;
    return t;
}

int main(int argc, char **argv) {
    String a("hello");
    a.print();
    cout << a << endl;
    String b = a;
    cout << b << endl;
    b.print();
    String c(b);
    c.print();
    cout << c << endl;
    cout << "input a string:" << endl;
    String d(NULL);
    cin >> d;
    cout << d << endl;
    String e = a + d;
    cout << e << endl;
    return 0;
}
