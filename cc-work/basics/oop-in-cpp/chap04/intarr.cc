/*
 * intarr.cc
 *
 * implementation class integer array.
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class IntArray {
private:
  enum { MAX_SIZE = 50 };
protected:
  int array[ MAX_SIZE ];
  int size;
public:
  IntArray();
  IntArray( const int &n );
  void setSize( const int &n );
  void output() const;
  int getSize() const;
  void setElement( const int &index, const int &elem );
  int getElement( const int &index ) const;
};

IntArray::IntArray() {
  size = 0;
}

IntArray::IntArray( const int &n ) {
  size = n;
}

void IntArray::setSize( const int &n ) {
  size = n;
}

void IntArray::output() const {
  int i;
  for ( i = 0; i < size; i++ ) {
    cout << array[ i ] << " ";
  }
  cout << endl;
}

int IntArray::getSize() const {
  return size;
}

void IntArray::setElement( const int &index, const int &elem ) {
  if ( index < 0 || index >= size ) {
    cerr << "Index out of boundary" << endl;
    exit( EXIT_FAILURE );
  }
  array[ index ] = elem;
}

int IntArray::getElement( const int &index ) const {
  if ( index < 0 || index >= size ) {
    cerr << "Index out of boundary" << endl;
    exit( EXIT_FAILURE );
  }
  return array[ index ];
}
// derive class Matrix from IntArray
class Matrix : public IntArray {
private:
  int rowSize;
  int colSize;
  string fname;
  using IntArray::setElement;
public:
  Matrix();
  Matrix( const int &row, const int &col, const string &file );
  void setRowSize( const int &row );
  void setColSize( const int &col );
  int getColSize() const;
  int getRowSize() const;
  void output() const;
  void input();
};

Matrix::Matrix() : IntArray() {
  colSize = 0;
  rowSize = 0;
  fname = "";
}

Matrix::Matrix( const int &row, const int &col, const string &file ) 
  : IntArray( row*col ) {
  rowSize = row;
  colSize = col;
  fname = file;
}

void Matrix::setRowSize( const int &row ) {
  rowSize = row;
}

void Matrix::setColSize( const int &col ) {
  colSize = col;
}

int Matrix::getRowSize() const {
  return rowSize;
}

int Matrix::getColSize() const {
  return colSize;
}

void Matrix::output() const {
  int i, j;
  for ( i = 0; i < rowSize; i++ ) {
    for ( j = 0; j < colSize; j++ ) {
      cout << getElement( j+i*colSize ) << " ";
    }
    cout << endl;
  }
}

void Matrix::input() {
  int i, index, j, tmp;
  if ( fname == "" ) {
    cerr << "Missing input file" << endl;
    exit( EXIT_FAILURE );
  }
  ifstream in;
  in.open( fname.c_str() );
  for ( i = 0; i < rowSize; i++ ) {
    for ( j = 0; j < colSize; j++ ) {
      in >> tmp;
      index = j + i * colSize;
      setElement( index, tmp );
    }
  }
  in.close();
}

int main() {
  Matrix one( 5, 5, "intarr.dat" );
  cout << "row is " << one.getRowSize() << endl;
  cout << "col is " << one.getColSize() << endl;
  one.input();
  one.output();
  return 0;
}
