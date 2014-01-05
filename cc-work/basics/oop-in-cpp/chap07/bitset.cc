/*
 * bitset.cc
 *
 * STL container bitset at a first glance
 */
#include <bitset>
#include <iostream>
using namespace std;

const unsigned featureCount = 8;
const unsigned Framed = 1;
const unsigned Bordered = 2;
const unsigned StdMenu = 4;
const unsigned Toolbar = 8;
const unsigned StatusBar = 16;

class Window {
public:
  Window( const string &n, unsigned f ) {
    name = n;
    features = bitset< featureCount >( f );
    createWindow();
  }
  Window( const char *n, unsigned f ) {
    name = n;
    features = bitset< featureCount >( f );
    createWindow();
  }
private:
  // simulate window creation by printing features to standard output
  void createWindow() {
    cout << endl << "***Window features for " << name
	 << " given bit mask " << features << ":" << endl;
    if ( features[ 0 ] ) {
      cout << "\tframed" << endl;
    }
    if ( features[ 1 ] ) {
      cout << "\tbordered" << endl;
    } 
    if ( features[ 2 ] ) {
      cout << "\twith standard menu" << endl;
    }
    if ( features[ 3 ] ) {
      cout << "\twith tool bar" << endl;
    }
    if ( features[ 4 ] ) {
      cout << "\twith status bar" << endl;
    }
  }
  string name;
  bitset< featureCount > features;
};

int main() {
  Window w1( "w1", Framed | Toolbar | StatusBar );
  Window w2( "w2", Toolbar | Framed | StatusBar );
  Window w3( "w3", Framed | StdMenu | StatusBar | Toolbar | Bordered );
  return 0;
}
