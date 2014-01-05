/*
 * rtti.cc
 *
 * a sample demonstrates run-time type identification mechinism in c++
 */
#include <iostream>
#include <string>
using namespace std;

class Book {
private:
  Book(); // title required
  string title;
public:
  Book( const string &t );
  virtual ~Book() {}
  virtual void printTitle() const;
};

Book::Book( const string &t ) {
  title = t;
}

void Book::printTitle() const {
  cout << "Title: " << title << endl;
}

class TextBook : public Book {
private:
  TextBook(); // title and level required
  int level;
public:
  TextBook( const string &t, const int &l );
  void printTitle() const;
  void printLevel() const;
};

TextBook::TextBook( const string &t, const int &l ) 
  : Book( t ) {
  level = l;
}

void TextBook::printTitle() const {
  cout << "Textbook ";
  Book::printTitle();
}

void TextBook::printLevel() const {
  cout << "Book level: " << level << endl;
}

class PulpFiction : public Book {
private:
  PulpFiction();
public:
  PulpFiction( const string &t );
  void printTitle() const;
};

PulpFiction::PulpFiction( const string &t ) 
  : Book( t ) {}
void PulpFiction::printTitle() const {
  cout << "Pulp ";
  Book::printTitle();
}

void printBookInfor( Book *book );

int main() {
  Book *ptr;
  int level;
  string title;
  int ans;
  cout << "Book's title? (no white space) ";
  cin >> title;
  do {
    cout << "1 == TextBook, 2 == PulpFiction " << endl;
    cin >> ans;
  } while ( ans < 1 || ans > 2 );
  if ( 1 == ans ) {
    cout << "Level? ";
    cin >> level;
    ptr = new TextBook( title, level );
  } else {
    ptr = new PulpFiction( title );
  }
  printBookInfor( ptr );
  return 0;
}

void printBookInfor( Book *ptr ) {
  ptr->printTitle();

  TextBook *tptr = dynamic_cast< TextBook *>( ptr );
  if ( tptr ) { // ptr points to a TextBook object
    tptr->printLevel(); // type safe: ptr of type TextBook
  }
}
