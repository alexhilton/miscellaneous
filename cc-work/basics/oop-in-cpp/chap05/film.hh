/*
 * class Film
 *
 * implementation of class Film.
 */
#ifndef _film_hh
#define _film_hh

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

class Film {
private:
  string title;
  string director;
  int time; // in minutes
  int quality; // 0 (bad) to 4 (top)
public:
  Film();
  virtual ~Film() {}
  void setTitle( const string &t );
  void setDirector( const string &t );
  void setTime( const int &t );
  void setQuality( const int &q );
  virtual void output() const;
  virtual void input( ifstream &in );
  static bool readInput( const char *fname, Film *film[], int size );
};

Film::Film() {
  title = "unkown";
  director = "unkown";
  time = 0;
  quality = 0;
}

void Film::setTitle( const string &t ) {
  title = t;
}

void Film::setDirector( const string &d ) {
  director = d;
}

void Film::setTime( const int &t ) {
  time = t;
}

void Film::setQuality( const int &q ) {
  quality = q;
}

// no use virtual keyword when defining method
void Film::input( ifstream &in ) {
  string inbuf;
  getline( in, inbuf );
  setTitle( inbuf );
  getline( in, inbuf );
  setDirector( inbuf );
  getline( in, inbuf );
  setTime( atoi( inbuf.c_str() ) );
  getline( in, inbuf );
  setQuality( atoi( inbuf.c_str() ) );
}

// another virtual method
void Film::output() const {
  cout << "Title: " << title << endl;
  cout << "Director: " << director << endl;
  cout << "Time: " << time << " mins" << endl;
  cout << "Quality: ";
  for ( int i = 0; i < quality; i++ ) {
    cout << "*";
  }
  cout << endl;
}

// derived class DirectorCut
class DirectorCut : public Film {
private:
  int reviseTime;
  string changes;
public:
  DirectorCut();
  void setReviseTime( const int &rt );
  void setChanges( const string &ch );
  virtual void output() const;
  virtual void input( ifstream &in );
};

DirectorCut::DirectorCut() : Film() {
  reviseTime = 0;
  changes = "unkown";
}

void DirectorCut::setReviseTime( const int &rt ) {
  reviseTime = rt;
}

void DirectorCut::setChanges( const string &ch ) {
  changes = ch;
}

void DirectorCut::input( ifstream &in ) {
  Film::input( in );
  string inbuf;
  getline( in, inbuf );
  setReviseTime( atoi( inbuf.c_str() ) );
  getline( in, inbuf );
  setChanges( inbuf );
}

// output method
void DirectorCut::output() const {
  Film::output();
  cout << "Revised time: " << reviseTime << endl;
  cout << "Changes: " << changes << endl;
}

// derived class ForeignFilm
class ForeignFilm : public Film {
private:
  string language;
public:
  ForeignFilm();
  void setLanguage( const string &lang );
  virtual void output() const;
  virtual void input( ifstream &in );
};

ForeignFilm::ForeignFilm() : Film() {
  language = "unkown";
}

void ForeignFilm::setLanguage( const string &lang ) {
  language = lang;
}

void ForeignFilm::input( ifstream &in ) {
  Film::input( in );
  string inbuf;
  getline( in, inbuf );
  setLanguage( inbuf );
}

void ForeignFilm::output() const {
  Film::output();
  cout << "Language: " << language << endl;
}

class SongAndDance : public Film {
private:
  string theme;
  string singer;
public:
  SongAndDance();
  void setTheme( const string &t );
  void setSinger( const string &s );
  virtual void input( ifstream &in );
  virtual void output() const;
};

SongAndDance::SongAndDance() : Film() {
  theme = "unkown";
  singer = "unkown";
}

void SongAndDance::setTheme( const string &t ) {
  theme = t;
}

void SongAndDance::setSinger( const string &s ) {
  singer = s;
}

void SongAndDance::input( ifstream &in ) {
  Film::input( in );
  string inbuf;
  getline( in, inbuf );
  setTheme( inbuf );
  setSinger( inbuf );
}

void SongAndDance::output() const {
  Film::output();
  cout << "Theme: " << theme << endl;
  cout << "Singer: " << singer << endl;
}
/*
 * class method: Film::readInput()
 * Reads data from an input file, dynamically creating the
 * appropirate Film object for each record group. For instance,
 * a ForeignFilm object is dynamically created if the data
 * represent a foreign film rather than a regular film or a
 * director's cut. Pointers to dynamically created objects are
 * stored in the array films of size n. Returns true to signal
 * success and false to signal failure.
 */
bool Film::readInput( const char *fname, Film *film[], int size ) {
  string inbuf;
  ifstream in( fname );
  if ( !in ) {
    return false;
  }
  /*
   * read until end-of-file. Records fall into groups. First record
   * in each group is a string that represents a Film type:
   *  "Film", "ForeignFilm" or "DirectorCut".
   * After reading type record, dynamically create an object of the
   * type (e.g., a ForeignFilm object), place it in the array film[],
   * and invoke its input method.
   */
  int next = 0;
  while ( getline( in, inbuf ) && next < size ) {
    if ( inbuf == "Film" ) {
      film[ next ] = new Film(); // regular film
    } else if ( inbuf == "ForeignFilm" ) {
      film[ next ] = new ForeignFilm(); // foreign film
    } else if ( inbuf == "DirectorCut" ) {
      film[ next ] = new DirectorCut(); // Director's cut
    } else if ( inbuf == "SongAndDance" ) {
      film[ next ] = new SongAndDance(); // song and dance opera
    } else {
      continue; // error occured, skip it
    }
    film[ next++ ]->input( in );
  }
  in.close();
  return true;
}

#endif // film.hh
