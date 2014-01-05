/*
 * task.cc
 *
 * a task scheduling simulation program.
 */
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include "timestamp.cc"
using namespace std;

class Task {
private:
  Task();
  Timestamp start;
  Timestamp finish;
  string id;
  string logfile;
public:
  Task( const string &ID ) {
    setID( ID );
    logfile = "log.dat";
    setStart();
    finish = start;
  }
  Task( const char *ID ) {
    setID( ID );
    logfile = "log.dat";
    setStart();
    finish = start;
  }
  ~Task() {
    logtofile();
  }

  void setStart( time_t st = 0 ) {
    start.set( st );
  }
  time_t getStart() const {
    return start.get();
  }

  string getStringStart() const {
    return start.getAsString();
  }

  void setFinish( time_t fh = 0 ) {
    finish.set( fh );
  }
  time_t getFinish() const {
    return finish.get();
  }
  string getStringFinish() const {
    return finish.getAsString();
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
    return difftime( getFinish(), getStart() );
  }

  void logtofile() {
    if ( getFinish() == getStart() ) {
      setFinish();
    }

    ofstream outfile( logfile.c_str(), ios::app );
    outfile << "\nID: " << id << endl;
    outfile << "\tstart: " << getStringStart();
    outfile << endl;
    outfile << "\tfinish: " << getStringFinish();
    outfile << endl;
    outfile << "\tDU: " << getDU();
    outfile << endl;
    outfile.close();
  }
};
