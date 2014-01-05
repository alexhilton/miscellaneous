/*
 * testing driver program for class film define in file
 * film.hh
 */
#include "film.hh"
int main() {
  const int n = 5;
  Film *film[ n ];

  // attempt to read input file and create objects
  if ( !Film::readInput( "film.dat", film, n ) ) {
    cerr << "Unable to read file film.dat" << endl;
    exit( EXIT_FAILURE );
  }

  // output
  int i;
  for ( i = 0; i < n; i++ ) {
    film[ i ]->output();
  }
  return 0;
}
