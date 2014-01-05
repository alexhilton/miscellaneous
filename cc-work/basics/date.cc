/*
 * date.cc
 * implement a date class to provide some methods about
 * date operation.
 */
#include <iostream>
#include <string>
using namespace std;

class Date {
private:
  int day;
  int week;
  int month;
  int year;
  string weekName() {
    switch ( week ) {
    case 1:
      return "Mon";
    case 2:
      return "Tue";
    case 3:
      return "Wed";
    case 4:
      return "Thu";
    case 5:
      return "Fri";
    case 6:
      return "Sat";
    case 7:
      return "Sun";
    default:
      cout << "Invalide week!" << endl;
      break;
    }
    return "";
  }
  string monthName() {
    switch ( month ) {
    case 1:
      return "Jan";
    case 2:
      return "Feb";
    case 3:
      return "Mar";
    case 4:
    return "Apr";
    case 5:
      return "May";
    case 6:
      return "Jun";
    case 7:
      return "Jul";
    case 8:
      return "Aug";
    case 9:
      return "Sep";
    case 10:
      return "Oct";
    case 11:
      return "Nov";
    case 12:
      return "Dec";
    }
    return "";
  }
  void reverse( string &str ) {
    int i = 0, j = str.length();
    while ( i < j ) {
      str[i] ^= str[j];
      str[j] ^= str[i];
      str[i] ^= str[j];
      i++, j--;
    }
  }
  string int2str( int n ) {
    string ret; 
    int i;
    while ( n % 10 != 0 ) {
      ret[ i++ ] = n % 10 + '0';
      n /= 10;
    }
    reverse( ret );
    return ret;
  }
public:
  Date() {;}
  Date( int &d ) {
    day = d;
  }
  Date( int &d, int &w ) {
    day = d;
    week = w;
  }
  Date( int &d, int &w, int &m ) {
    day = d;
    week = w;
    month = m;
  }
  Date( int &d, int &w, int &m, int &y ) {
    day = d;
    week = w;
    month = m;
    year = y;
  }
  void setDay( int &d ) {
    day = d;
  }
  void setWeek( int &w ) {
    week = w;
  }
  void setMonth( int &m ) {
    month = m;
  }
  void setYear( int &y ) {
    year = y;
  }
  void setDate( int &d, int &w, int &m, int &y ) {
    day = d;
    week = w;
    month = m;
    year = y;
  }
  int getDay() {
    return day;
  }
  int getWeek() {
    return week;
  }
  int getMonth() {
    return month;
  }
  int getYear() {
    return year;
  }
  //string getDateAsString() {
   // return monthName(); //+ int2str( day ) + int2str( year ) + ", " + weekName();
  //}
  void printDate() {
    cout << monthName() << " " << day << "," << year << " " << weekName() << endl;
  }
};

int main() {
  int d, w, m, y;
  Date one;
  char flag;
  while ( true ) {
    cout << " day, week, month, year: " << endl;
    cin >> d >> w >> m >> y;
    one.setDay( d );
    one.setWeek( w );
    one.setMonth( m );
    one.setYear( y );
    cout << "get date as string: " << endl;
    //cout << one.getDateAsString() << endl;
    cout << "print date: " << endl;
    one.printDate();
    cout << "Continue?(y/n): " ;
    cin >> flag;
    if ( flag == 'n' ) {
      break;
    }
  }
  return 0;
}
