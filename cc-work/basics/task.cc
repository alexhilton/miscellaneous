/*
 * task.cc
 * create a task class to represent a task to be scheduled.
 */
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
using namespace std;

class TimeStamp {
private:
  string extract( int offset, int count ) const {
    string timeString = ctime( &stamp );
    return timeString.substr( offset, count );
  }
  time_t stamp;
public:
  void set( long s = 0 ) {
    if ( s <= 0 ) {
      stamp = time( 0 );
    } else {
      stamp = s;
    }
  }
  time_t get() const {
    return stamp;
  }
  string getAsString() const {
    return extract( 0, 24 );
  }
  string getYear() const {
    return extract( 20, 4 );
  }
  string getMonth() const {
    return extract( 4, 3 );
  }
  string getDay() const {
    return extract( 0, 3 );
  }
  string getHour() const {
    return extract( 11, 2 );
  }
  string getMinute() const {
    return extract( 14, 2 );
  }
  string getSecond() const {
    return extract( 17, 2 );
  }
};
class Task {
private:
  Task(); // default constructor explicitly hidden
  TimeStamp st;
  TimeStamp ft;
  string id;
  string logFile;
public:
  // constructor-destructors
  Task( const string &ID ) {
    setID( ID );
    logFile = "log.dat";
    setST();
    ft = st; // no duration yet
  }
  Task( const char *ID ) {
    setID( ID );
    logFile = "log.dat";
    setST();
    ft = st; // no duration yet
  }
  ~Task() {
    logToFile();
  }
  // set-get methods
  void setST( time_t ST = 0 ) {
    st.set( ST );
  }
  time_t getST() const {
    return st.get();
  }

  void setFT( time_t FT = 0 ) {
    ft.set( FT );
  }
  time_t getFT() const {
    return ft.get();
  }
  string getStrST() const {
    return st.getAsString();
  }

  string getStrFT() const {
    return ft.getAsString();
  }

  void setID( const string &ID ) {
    id = ID;
  }
  void setID( const char *ID ) {
    id = ID;
  }
  string getID() const {
    return id;
  }
  double getDU() const {
    return difftime( getFT(), getST() );
  }
  void logToFile() {
    // set finish if duration still 0
    if ( getFT() == getST() ) {
      setFT();
    }
    // log the Task's vital statistics
    ofstream outfile( logFile.c_str(), ios::app );
    outfile << "\nID: " << id << endl;
    outfile << " ST: " << getStrST();
    outfile << " FT: " << getStrFT();
    outfile << " DU: " << getDU();
    outfile << endl;
    outfile.close(); 
  }
};

int main() {
  time_t now = time( 0 );
  Task t1( "Defrost pissas" ), t2( "Open beer" );
  Task t3( "Eat pissas and drink beer" );
  t1.setST( now );
  t1.setFT( now+3600 );  // an hour from now
  t2.setST( t1.getFT() ); // when pissas defrosted
  t2.setFT( t2.getST() + 2 ); // fast work
  t3.setST( t2.getFT() + 1 ); // slight delay
  t3.setFT( t3.getST() + 7200 ); // leisure meal

  return 0;
}
