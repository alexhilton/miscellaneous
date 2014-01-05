/*
 * getdate.c
 * a function to get date from a string using sscanf function.
 */
#include <stdio.h>

int main( int argc, char *argv[] ) {
  int nf; /* used to check error by sscanf */
  int n;
  int month, day, year;
  static char date[] = "   12/  2 / 2008 ";

  printf( "Extracting from '%s'\n", date );

  nf = sscanf( date, "%d /%d /%d%n", &month, &day, &year, &n );

  printf( "%02d/%02d/%04d nf = %d, n = %d\n", month, day, year, nf, n );

  if ( nf >= 3 ) {
    printf( "Remainder = '%s'\n", &date[ n ] );
  }
  return 0;
}
