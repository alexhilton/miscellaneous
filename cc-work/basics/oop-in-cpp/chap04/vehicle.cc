/*
 * vehicle.cc
 *
 * implement a class vehicle
 * and derive two classes from it.
 */
#include <iostream>
#include <string>
using namespace std;

class Vehicle {
private:
  string make; // manufacture name
  string model;
  int year; // year of production
  double price;
public:
  Vehicle();
  Vehicle( const string &mk, const string &mod, 
	   const int &y, const double &p );
  void setMake( const string &mk );
  string getMake() const;
  void setModel( const string &mod );
  string getModel() const;
  void setYear( const int &y );
  int getYear() const;
  void setPrice( const double &p );
  double getPrice() const;
  void output() const;
  Vehicle copy();
};

Vehicle::Vehicle() {
  make = "unkown";
  model = "unkown";
  year = 1800;
  price = 10000.00;
}

Vehicle::Vehicle( const string &mk, const string &mod, 
		  const int &y, const double &p ) {
  make = mk;
  model = mod;
  year = y;
  price = p;
}

void Vehicle::setMake( const string &mk ) {
  make = mk;
}

string Vehicle::getMake() const {
  return make;
}

void Vehicle::setModel( const string &mod ) {
  model = make;
}

string Vehicle::getModel() const {
  return model;
}

void Vehicle::setYear( const int &y ) {
  year = y;
}

int Vehicle::getYear() const {
  return year;
}

void Vehicle::setPrice( const double &p ) {
  price = p;
}

double Vehicle::getPrice() const {
  return price;
}

void Vehicle::output() const {
  cout << "Make: " << make << endl;
  cout << "Model: " << model << endl;
  cout << "Year of Production: " << year << endl;
  cout << "Price: " << price << endl;
}

Vehicle Vehicle::copy() {
  Vehicle tmp( make, model, year, price );
  return tmp;
}

// derived class Car
class Car : public Vehicle {
private:
  double weight; // in kilogram
  double speed; // in kilometer per hour
  using Vehicle::output;
public:
  Car();
  Car( const double &w, const double &s, 
       const string &mk, const string &mod, const int &y, const double &p );
  void setWeight( const double &w );
  double getWeight() const;
  void setSpeed( const double &d );
  double getSpeed() const;
  void output() const;
  Car copy();
};

Car::Car() : Vehicle() {
  weight = 2000;
  speed = 60;
}

Car::Car( const double &w, const double &s,
	  const string &mk, const string &mod, const int &y, const double &p )
  : Vehicle( mk, mod, y, p ) {
  weight = w;
  speed = s;
}

void Car::setWeight( const double &w ) {
  weight = w;
}

double Car::getWeight() const {
  return weight;
}

void Car::setSpeed( const double &s ) {
  speed = s;
}

double Car::getSpeed() const {
  return speed;
}

void Car::output() const {
  Vehicle::output();
  cout << "Weight: " << weight << endl;
  cout << "Speed: " << speed << endl << endl;
}

Car Car::copy() {
  Car tmp;
  tmp.setWeight( weight );
  tmp.setSpeed( speed );
  tmp.setMake( getMake() );
  tmp.setModel( getModel() );
  tmp.setYear( getYear() );
  tmp.setPrice( getPrice() );
  return tmp;
}

// derive another class Truck from Vehicle
class Truck : public Vehicle {
private:
  double load; // in ton
  double length; // in meters
  using Vehicle::output;
public:
  Truck();
  Truck( const double &l, const double &len, 
	 const string &mk, const string &mod, const int &y, const double &p );
  void setLoad( const double &l );
  double getLoad() const;
  void setLength( const double &len );
  double getLength() const;
  void output() const;
  Truck copy();
};

Truck::Truck() : Vehicle() {
  load = 20;
  length = 30;
}

Truck::Truck( const double &l, const double &len,
	      const string &mk, const string &mod, const int &y, 
	      const double &p ) : Vehicle( mk, mod, y, p ) {
  load = l;
  length = len;
}

void Truck::setLoad( const double &l ) {
  load = l;
}

double Truck::getLoad() const {
  return load;
}

void Truck::setLength( const double &len ) {
  length = len;
}

double Truck::getLength() const {
  return length;
}

void Truck::output() const {
  Vehicle::output();
  cout << "Load: " << load << endl;
  cout << "Length: " << length << endl << endl;
}

Truck Truck::copy() {
  Truck tmp;
  tmp.setMake( getMake() );
  tmp.setModel( getModel() );
  tmp.setYear( getYear() );
  tmp.setPrice( getPrice() );
  tmp.setLoad( load );
  tmp.setLength( length );
  return tmp;
}

int main() {
  Car one( 109, 199, "Bench", "NY-0-Z-1", 2008, 1890 );
  one.output();
  Truck two( 309.98, 234, "Fond", "CT-2-B-4", 2009, 3456 );
  two.output();
  return 0;
}
