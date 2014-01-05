/*
 * film.cc
 * a project to develop a program to track a film, which has name, length
 * cutting, director and quality attributes.
 */
#include <iostream>
using namespace std;

/*
 * class Film.
 */
class Film {
private:
  string title;
  string director;
  int time; // in minutes
  int quality; // 0(bad) to 4(best).
public:
  void storeTitle( const string &t ) {
    title = t;
  }
  void storeTitle( const char *t ) {
    title = t;
  }
  void storeDirector( const string &d ) {
    director  = d; 
  }
  void storeDirector( const char *d ) {
    director = d;
  }
  void storeTime( int t ) {
    time = t;
  }
  void storeQuality( int q ) {
    quality = q;
  }
  void output() const;
};
void Film::output() const {
  int i;
  cout << "Title: " << title << endl;
  cout << "Director: " << director << endl;
  cout << "Time: " << time << endl;
  cout << "Quality: " << quality << endl;

  for ( i = 0; i < quality; i++ ) {
    cout << "*";
  }
  cout << endl;
}

/* derived class DirectorCut */
class DirectorCut : public Film {
private:
  int revTime;
  string change;
public:
  void storeRevTime( int t ) {
    revTime = t;
  }
  void storeChange( const string &s ) {
    change = s;
  }
  void storeChange( const char *s ) {
    change = s;
  }
  void output() const;
};

void DirectorCut::output() const {
  Film::output();
  cout << "Revised time: " << revTime << " mins" << endl;
  cout << "Changes: " << change << endl;
}

/* another derived class */
class ForeignFilm : public Film {
private:
  string language;
public:
  void storeLanguage( const string &l ) {
    language = l;
  }
  void storeLanguage( const char *l ) {
    language = l;
  }
  void output() const;
};

void ForeignFilm::output() const {
  Film::output();
  cout << "Languages: " << language << endl;
}

// derive an additional class Documentary from class Film.
class Documentary : public Film {
private:
  string producer;
  string presents; // present company
public:
  void setProducer( const string &pro );
  void setPresents( const string &pre );
  void output() const;
};

void Documentary::setProducer( const string &pro ) {
  producer = pro;
}

void Documentary::setPresents( const string &pre ) {
  presents = pre;
}

void Documentary::output() const {
  Film::output();
  cout << "Producer: " << producer << endl;
  cout << "Presents: " << presents << endl;
}

int main() {
  Film f;
  f.storeTitle( "Rear window" );
  f.storeDirector( "Alfred Eitchcock" );
  f.storeTime( 112 );
  f.storeQuality( 4 );
  cout << "Film--" << endl;
  f.output();
  cout << endl;

  DirectorCut d;
  d.storeTitle( "Jail Bait" );
  d.storeDirector( "Ed Wood" );
  d.storeTime( 70 );
  d.storeQuality( 2 );
  d.storeRevTime( 72 );
  d.storeChange( "Extra footage not in original included" );
  cout << "DirectorCut---" << endl;
  d.output();
  cout << endl;

  ForeignFilm ff;
  ff.storeTitle( "Jules and Jim" );
  ff.storeDirector( "Francois Truffaut" );
  ff.storeTime( 104 );
  ff.storeQuality( 4 );
  ff.storeLanguage( "French" );
  cout << "ForeignFilm----" << endl;
  ff.output();
  cout << endl;

  Documentary doc;
  doc.storeTitle( "The Incredibles" );
  doc.storeDirector( "Michael Bay" );
  doc.storeTime( 130 );
  doc.storeQuality( 5 );
  doc.setProducer( "Bob Seger" );
  doc.setPresents( "Pixar Animation" );
  doc.output();

  return 0;
}
