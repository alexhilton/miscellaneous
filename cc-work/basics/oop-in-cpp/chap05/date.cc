/*
 * implementation of Class Date
 * date.cc
 *
 */
#include <iostream>
#include <string>
using namespace std;

class Date {
private:
  int year;
  int month;
  int day;
  string monthName;
  string datestr;
  string convert() const {
    switch ( month ) {
    case 1:
      return "January";
    case 2:
      return "Feburary";
    case 3:
      return "March";
    case 4:
      return "April";
    case 5:
      return "May";
    case 6:
      return "June";
    case 7:
      return "July";
    case 8:
      return "Auguest";
    case 9:
      return "September";
    case 10:
      return "October";
    case 11:
      return "November";
    case 12:
      return "December";
    default:
      return "";
    }
  }
public:
  Date();
  Date( const int &y, const int &m, const int &d );
  virtual ~Date() {}
  virtual void print() const;
  void setYear( const int &y );
  int getYear() const;
  string getYearString() const;
  void setMonth( const int &m );
  int getMonth() const;
  string getMonthString() const;
  string getMonthName() const;
  void setDay( const int &d );
  int getDay() const;
  string getDayString() const;
  string getDateString() const;
  string itostr( const int &n ) const;
};

Date::Date() {
  year = 2000;
  month = 1;
  day = 1;
  datestr = "1/1/2000";
  monthName = convert();
}

Date::Date( const int &m, const int &d, const int &y ) {
  year = y;
  month = m;
  day = d;
  monthName = convert();
  datestr = itostr( month ) + itostr( day ) + itostr( year );
}

void Date::setYear( const int &y ) {
  year = y;
}

int Date::getYear() const {
  return year;
}

string Date::getYearString() const {
  return itostr( year );
}

void Date::setMonth( const int &m ) {
  month = m;
}

int Date::getMonth() const {
  return month;
}

string Date::getMonthString() const {
  return itostr( month );
}

string Date::getMonthName() const {
  return monthName;
}

void Date::setDay( const int &d ) {
  day = d;
}

int Date::getDay() const {
  return day;
}

string Date::getDayString() const {
  return itostr( day );
}

string Date::getDateString() const {
  return datestr;
}

void Date::print() const {
  cout << month << "-" << day << "-" << year << endl;
}

string Date::itostr( const int &n ) const {
  string str;
  int i;
  int m = n;
  int k = 0;
  while ( m % 10 > 0 ) {
    i = m % 10;
    str[ k++ ] = i + '0';
    m /= 10;
  }
  str[ k ] = '\0';
  return str;
}

// derive class ShortDate from class Date
class ShortDate : public Date {
public:
  virtual void print() const;
  ShortDate() : Date() {}
  ShortDate( const int &m, const int &d, const int &y ) 
    : Date( m, d, y ) {}
};

void ShortDate::print() const {
  cout << getDay() << "-" << getMonth() << "-" << getYear() << endl;
}

// derive another class MediumeDate from class Date
class MediumeDate : public Date {
private:
  string monthNameShort;
  void getMonthNameShort() {
    monthNameShort = getMonthName().substr( 0, 3 );
  }
public:
  virtual void print() const;
  MediumeDate() : Date() {
    getMonthNameShort();
  }
  MediumeDate( const int &m, const int &d, const int &y ) 
    : Date( m, d, y ) { 
    getMonthNameShort();
  }
};

void MediumeDate::print() const {
  cout << monthNameShort << '.' << getDay() << ", " << getYear() << endl;
}

// derive another class from Date
class LongDate : public Date {
public:
  LongDate() : Date() {}
  LongDate( const int &m, const int &d, const int &y ) 
    : Date( m, d, y ) {}
  virtual void print() const {
    cout << getMonthName() << " " << getDay() << "," << getYear() << endl;
  }
};

int main() {
  Date one; // using default constructor
  Date two( 9, 2, 2009 );
  // cout << one.getMonthName() << endl;
  // cout << one.getMonthName().substr( 0, 3 ) << endl;
  one.print();
  two.print();
  ShortDate three; // using default constructor
  ShortDate four( 9, 2, 2009 );
  three.print();
  four.print();
  MediumeDate five; // default
  MediumeDate six( 9, 2, 2009 );
  five.print();
  six.print();
  LongDate seven;
  LongDate eight( 9, 2, 2009 );
  seven.print();
  eight.print();
  return 0;
}

  
