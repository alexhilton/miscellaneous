/*
 * window.cc
 *
 * Implement a hierarchy of class windows.
 * window, FrameWindow, MenuWindow, Dialog,
 */
#include <string>
#include <iostream>
using namespace std;

#define SCREEN 24

// abstract class Window
class Window {
private:
  int x0, y0; // left-top co-ordinate
  int length; // length of window
  int width; // width of window
  string caption; // caption or title of the window
public:
  Window() {
    x0 = 0;
    y0 = 0;
    length = 40;
    width = 12;
    caption = "Window";
  }
  Window( const int &x, const int &y, const int &l, const int &w, 
	  const string &c ) {
    x0 = x;
    y0 = y;
    length = l;
    width = w;
    caption = c;
  }
  void setPosition( const int &x, const int &y ) {
    x0 = x;
    y0 = y;
  }
  int getPositionX() const {
    return x0;
  }
  int getPositionY() const {
    return y0;
  }

  void setLength( const int &l ) {
    length = l;
  }
  int getLength() const {
    return length;
  }

  void setWidth( const int &w ) {
    width = w;
  }
  int getWidth() const {
    return width;
  }

  void setCaption( const string &c ) {
    caption = c;
  }
  string getCaption() const {
    return caption;
  }
  virtual ~Window() {}
  virtual void create( const string &c ) {
    caption = c;
  }

  virtual void show() const {
    int i;
    for ( i = 0; i < x0; i++ ) {
      cout << endl;
    }
    printHeader();
    printBody();
    printTail();
  }

  virtual void move( const int &nx, const int &ny ) {
    setPosition( nx, ny );
    show();
  }

  virtual void hide() {
    int i;
    for ( i = 0; i < SCREEN; i++ ) {
      cout << endl;
    }
  }

  virtual void destroy() {
    int i;
    for ( i = 0; i < SCREEN; i++ ) {
      cout << endl;
    }
  }
protected:
  void printHeader() const {
    int i;
    cout << "+";
    for ( i = 0; i < length-2; i++ ) {
      cout << "-";
    }
    cout << "+" << endl;
    cout << "| " << caption;
    int tmp = length - caption.length() - 3;
    for ( i = 0; i < tmp; i++ ) {
      cout << " ";
    }
    cout << "|" << endl;
    for ( i = 0; i < length; i++ ) {
      cout << "-";
    }
    cout << endl;
  }

  void printBody() const {
    int i;
    int j;
    for ( i = 0; i < width-2; i++ ) {
      cout << "|";
      for ( j = 0; j < length-2; j++ ) {
	cout << " ";
      }
      cout << "|" << endl;
    }
  }

  void printTail() const {
    int i;
    cout << "+";
    for ( i = 0; i < length-2; i++ ) {
      cout << "-";
    }
    cout << "+" << endl;
  }
};

// derive class from 
class FrameWindow : public Window {
private:
  int status;
  string translate() const {
    switch ( status ) {
    case 0:
      return "0 status";
    case 1:
      return "1 status";
    case 2:
      return "2 status";
    default:
      return "";
    }
  }
  void printStatus() const {
    int i;
    for ( i = 0; i < getLength(); i++ ) {
      cout << "-";
    }
    cout << endl;
    cout << "| status: " << translate();
    int tmp;
    tmp = getLength()-2*translate().length()-3;
    for ( i = 0; i < tmp; i++ ) {
      cout << " ";
    }
    cout << "|" << endl;
  }
public:
  void setStatus( const int &s ) {
    status = s;
  }
  int getStatus() const {
    return status;
  }
  virtual void create( const string &c ) {
    setCaption( c );
  }
  FrameWindow() : Window() {
    status = 0;
  }

  FrameWindow( const int &x, const int &y, const int &l, const int &w,
	       const string &c, const int &s )
    : Window( x, y, l, w, c ) {
    status = s;
  }

  virtual void show() const {
    int i;
    for ( i = 0; i < getPositionX(); i++ ) {
      cout << endl;
    }
    printHeader();
    printBody();
    printStatus();
    printTail();
  }

  virtual void move( const int &nx, const int &ny ) {
    setPosition( nx, ny );
    show();
  }

  virtual void hide() const {
    int i;
    for ( i = 0; i < SCREEN; i++ ) {
      cout << endl;
    }
  }

  virtual void destory() const {
    int i;
    for ( i = 0; i < SCREEN; i++ ) {
      cout << endl;
    }
  }
};

// derive another class Dialog from Window
class Dialog : public Window {
private:
  string button1;
  string button2;
  void printButton() const {
    int i;
    cout << "|";
    int tmp = getLength()-2 - (button1.length() + button2.length() + 6);
    for ( i = 0; i < tmp; i++ ) {
      cout << " ";
    }
    cout << button1 << "   " << button2 << "   " << "|" << endl;
  }
public:
  Dialog() : Window() {
    button1 = "OK";
    button2 = "Cancel";
  }

  Dialog( const int &x, const int &y, const int &l, const int &w,
	  const string &c, const string &b1, const string &b2 )
    : Window( x, y, l, w, c ) {
    button1 = b1;
    button2 = b2;
  }

  virtual void create( const string &c ) {
    setCaption( c );
  }

  virtual void show() const {
    int i;
    for ( i = 0; i < getPositionX(); i++ ) {
      cout << endl;
    }
    printHeader();
    printBody();
    printButton();
    printTail();
  }

  virtual void move( const int &nx, const int &ny ) {
    setPosition( nx, ny );
    show();
  }

  virtual void hide() const {
    int i;
    for ( i = 0; i < SCREEN; i++ ) {
      cout << endl;
    }
  }

  virtual void destroy() const {
    int i;
    for ( i = 0; i < SCREEN; i++ ) {
      cout << endl;
    }
  }
};

// derive another class MenuWindow from Window
class MenuWindow : public Window {
private:
  string *menu;
  int size;
  void printMenu() const {
    int i;
    int tmp = getLength() - 3 - (size - 1);
    for ( i = 0; i < size; i++ ) {
      tmp -= menu[ i ].length();
    }
    cout << "|";
    for ( i = 0; i < size; i++ ) {
      cout << " " << menu[ i ];
    }
    for ( i = 0; i < tmp; i++ ) {
      cout << " ";
    }
    cout << "|" << endl;
    for ( i = 0; i < getLength(); i++ ) {
      cout << "-";
    }
    cout << endl;
  }
public:
  MenuWindow() : Window() {
    size = 6;
    menu = new string[ size ];
    menu[ 0 ] = "File";
    menu[ 1 ] = "Edit";
    menu[ 2 ] = "View";
    menu[ 3 ] = "Tools";
    menu[ 4 ] = "Window";
    menu[ 5 ] = "Help";
  }

  MenuWindow( const int &x, const int &y, const int &l, const int &w,
	      const string &c, const int &s, const string m[] )
    : Window( x, y, l, w, c ) {
    menu = new string[ size = s ];
    int i;
    for ( i = 0; i < size; i++ ) {
      menu[ i ] = m[ i ];
    }
  }

  ~MenuWindow() {
    delete [] menu;
  }

  void setSize( const int &s ) {
    size = s;
  }

  int getSize() const {
    return size;
  }

  void setMenu( const string m[] ) {
    int i;
    for ( i = 0; i < size; i++ ) {
      menu[ i ] = m[ i ];
    }
  }

  virtual void create( const string &c ) {
    setCaption( c );
  }

  virtual void show() const {
    int i;
    for ( i = 0; i < getPositionX(); i++ ) {
      cout << endl;
    }

    printHeader();
    printMenu();
    printBody();
    printTail();
  }

  virtual void hide() const {
    int i;
    for ( i = 0; i < SCREEN; i++ ) {
      cout << endl;
    }
  }

  virtual void move( const int &nx, const int &ny ) {
    setPosition( nx, ny );
    show();
  }

  virtual void destory() const {
    int i;
    for ( i = 0; i < SCREEN; i++ ) {
      cout << endl;
    }
  }
};

int main() {
  char ch;
  Window one;
  one.show();
  cout << "input 'n' to continue...";
  cin >> ch;
  one.destroy();
  FrameWindow two;
  two.show();
  cout << "input 'n' to continue...";
  cin >> ch;
  two.destroy();
  Dialog three;
  three.show();
  cout << "input 'n' to continue...";
  cin >> ch;
  three.destroy();
  MenuWindow four;
  four.show();
  cout << "input 'n' to continue...";
  cin >> ch;
  return 0;
}
