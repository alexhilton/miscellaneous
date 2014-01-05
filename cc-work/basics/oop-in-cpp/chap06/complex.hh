/*
 * implementation of class Complex, which maniputlates complex number
 * arithmetic operations in Mathmatical sense.
 */
#include <iostream>
#include <cmath>
using namespace std;

class Complex {
private:
  double real; // real part of complex
  double imag; // imaginary part of complex
public:
  Complex();
  Complex( double r );
  Complex( double r, double i );

  void write() const;
  void setReal( double r );
  double getReal() const;
  void setImag( double i );
  double getImag() const; 

  // arithmetic operations, implemented by operator overloading
  Complex operator+( const Complex &u ) const;
  Complex operator-( const Complex &u ) const;
  Complex operator*( const Complex &u ) const;
  Complex operator/( const Complex &u) const;
  Complex operator~() const; // conjugate of complex
  double operator!() const; // absolute value of complex
  bool operator==( const Complex &u ) const;
  Complex operator-() const;
  // way to declaration for I/O operator '<<' and '>>'
  friend ostream &operator<<( ostream &out, const Complex &u );
  friend istream &operator>>( istream &in, Complex &u ); 
};

Complex::Complex() {
  real = imag = 0.0f;
}

Complex::Complex( double r ) {
  real = r;
  imag = 0.0f;
}

Complex::Complex( double r, double i ) {
  real = r;
  imag = i;
}

void Complex::write() const {
  double i = imag;
  string op;
  if ( imag < 0 ) {
    op = " - ";
    i *= -1;
  } else {
    op = " + ";
  }
  cout << real << op << i << "i" << endl;
}

void Complex::setReal( double r ) {
  real = r;
}

double Complex::getReal() const {
  return real;
}

void Complex::setImag( double i ) {
  imag = i;
}

double Complex::getImag() const {
  return imag;
}

// arithmetic operations, by operator overloading
Complex Complex::operator+( const Complex &u ) const {
  Complex v( real + u.getReal(), imag + u.getImag() );
  return v;
}

Complex Complex::operator-( const Complex &u ) const {
  Complex v( real - u.getReal(), imag - u.getImag() );
  return v;
}

Complex Complex::operator*( const Complex &u ) const {
  Complex v( real * u.getReal(), imag * u.getImag() );
  return v;
}

Complex Complex::operator/( const Complex &u ) const {
  double abssq = u.getReal() * u.getReal() - u.getImag() * u.getImag();
  if ( abssq == 0.0f ) {
    cerr << "Divided by 0" << endl;
    exit( EXIT_FAILURE );
  }
  Complex v( (real*u.getReal() + imag*u.getImag()) / abssq,
	     (imag*u.getReal() + real*u.getImag()) / abssq );
  return v;
}

Complex Complex::operator~() const {
  Complex v( real, -1 * imag );
  return v;
}

double Complex::operator!() const {
  return sqrt( real * real + imag * imag );
}

bool Complex::operator==( const Complex &u ) const {
  return real == u.getReal() && imag == u.getImag();
}

Complex Complex::operator-() const {
  Complex v( -1*real, -1*imag );
  return v;
}

// standard way to overload output operator '<<'
ostream &operator<<( ostream &out, const Complex &u ) {
  double i = u.getImag();
  string op;
  if ( i < 0 ) {
    op = " - ";
    i *= -1;
  } else {
    op = " + ";
  }
  out << u.getReal() << op << i << "i" << endl;
  return out;
}

// standard way to overload input operator '>>'
istream &operator>>( istream &in, Complex &u ) {
  return in >> u.real >> u.imag;
}
