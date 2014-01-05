/*
 * timestampdriver.cc
 *
 * dirver to timestamp.cc
 */
#include "timestamp.cc"
using namespace std;

void dump( const Timestamp &t );

int main() {
  Timestamp ts;
  time_t now = time( 0 );

  ts.set();
  dump( ts );

  ts.set( now + 20000 );
  dump( ts );

  ts.set( now - 30000 );
  dump( ts );

  ts.set( -999 );
  dump( ts );

  return 0;
}

void dump( const Timestamp &ts ) {
  cout << endl;
  cout << "testing methods" << endl;
  cout << ts.get() << endl;
  cout << ts.getAsString() << endl;
  cout << ts.getYear() << endl;
  cout << ts.getMonth() << endl;
  cout << ts.getDay() << endl;
  cout << ts.getHour() << endl;
  cout << ts.getMinute() << endl;
  cout << ts.getSecond() << endl;
}
