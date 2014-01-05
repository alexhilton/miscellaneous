/*
 * Implement the echo command for windows
 */
#include <iostream>
#include <string>
using namespace std;

int main( int argc, char **argv ) {
    if ( argc <= 1 ) {
        return 0;
    }
    string str;
    while ( --argc > 0 ) {
        str.append( *++argv );
        str.append( " " );
    }
    cout << str << endl;
    return 0;
}
