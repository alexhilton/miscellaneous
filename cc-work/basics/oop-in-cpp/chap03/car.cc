/*
 * car.cc
 * class Car.
 */
#include <iostream>
using namespace std;

class Car {
private:
  string make;
  string model;
  int prodYear;
  double price;
public:
  Car() {}
  Car( const string &m ) {
    make = m;
  }
  Car( const string  &m, const string &mod ) {
    make = m;
    model = mod;
  }
  Car( const string &m, const string &mod, const int &p ) {
    make = m;
    model = mod;
    prodYear = p;
  }
  Car( const string &m, const string &mod, const int &p, const double &pr ) {
    make = m;
    model = mod;
    prodYear = p;
    price = pr;
  }
  void setMake( const string &m );
  void setModel( const string &m );
  void setYear( const int &p );
  void setPrice( const double &p );
  string getMake() const;
  string getModel() const;
  int getYear() const;
  double getPrice() const;
  void compare( const Car &another ) const;
  void output() const;
};

void Car::setMake( const string &m ) {
  make = m;
}

void Car::setModel( const string &m ) {
  model = m;
}

void Car::setYear( const int &y ) {
  prodYear = y;
}

void Car::setPrice( const double &p ) {
  price = p;
}

string Car::getMake() const {
  return make;
}

string Car::getModel() const {
  return model;
}

int Car::getYear() const {
  return prodYear;
}

double Car::getPrice() const {
  return price;
}

void Car::compare( const Car &another ) const {
  if ( prodYear < another.prodYear ) {
    cout << make << " is earlier than " << another.make << endl;
  } else {
    cout << make << " is later than " << another.make << endl;
  }
  if ( price > another.price ) {
    cout << make << " is more expensive than " << another.make << endl;
  } else {
    cout << make << " is cheaper than " << another.make << endl;
  }
  cout << endl;
}

void Car::output() const {
  cout << "Make: " << make << endl;
  cout << "Model: " << model << endl;
  cout << "Production Year: " << prodYear << endl;
  cout << "Price: " << price << endl;
  cout << "***************************************" << endl;
}

int main() {
  Car one;
  Car two( "Font" );
  Car three( "Volvo", "Civic" );
  Car four( "Toyota", "Home", 1999 );
  Car five( "Bench", "Business", 2008, 345678912.23 );
  one.setMake( "Fond" );
  one.setModel( "Civic" );
  one.setYear( 1988 );
  one.setPrice( 23456.90 );
  two.setModel( "Business" );
  two.setYear( 2005 );
  two.setPrice( 200000 );
  three.setYear( 2003 );
  three.setPrice( 23405.09 );
  four.setPrice( 12345.23 );
  one.output();
  two.output();
  three.output();
  four.output();
  five.output();
  one.compare( two );
  two.compare( three );
  three.compare( four );
  four.compare( five );
  return 0;
}
