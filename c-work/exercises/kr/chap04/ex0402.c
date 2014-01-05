/*
 * ex0402.c
 *
 * write a function atof which convert string of floating-
 * point number into its numeric value, exponentation capable
 */
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "getline.h"

double atof( char s[ ] );

int main( int argc, char *argv[ ] ) {
  FILE *in, *out;

  in = fopen( "input.dat", "r" );
  if ( in == NULL ) {
    perror( "input.dat" );
    return 1;
  }
  out = fopen( "output.dat", "w" );
  if ( out == NULL ) {
    perror( "output.dat" );
    return 1;
  }
  double val;
  char str[ 128 ];
  while ( getline( in, str, 128 ) > 0 ) {
    /*  printf( "before conversion: '%s'\n", str ); */
    val = atof( str );
    fprintf( out, "atof('%s') = %g\n", str, val );
  }

  fclose( in );
  fclose( out );

  return 0;
}


/*
 * atof
 *
 * val = atof( str ).
 * assume str is legal C string.
 * allow str has leading white spaces
 * str is either 'nnn.nnnn' or 'nnn.nnne9', e or E is option
 * + or - is option, leading zero of exponentation is allowed.
 */
double atof( char str[ ] ) {
  double val = 0.0;
  char *p = str;
  /* deal with leading white spaces */
  for ( ; isspace( *p ); p++ )
    ;
  char sign; 
  sign = ( *p == '-' ) ? '-' : '+';
  if ( *p == '-' || *p == '+' ) {
    p++;
  }

  while ( isdigit( *p ) ) {
    val = val * 10.0 + ( *p - '0' );
    p++;
  }
  if ( *p == '.' ) {
    p++;
  }
  double power = 1.0;
  for ( ; isdigit( *p ); p++ ) {
    val = val * 10.0 + ( *p - '0' );
    power *= 10.0;
  }

  val /= power;
  if ( sign == '-' ) {
    val *= -1;
  }
  
  if ( *p == 'e' || *p == 'E' ) {
    p++;
  }
  sign = ( *p == '-' ) ? '-' : '+';
  if ( *p == '-' || *p == '+' ) {
    p++;
  }

  /* deal with leading zeros of exponentation */
  while ( *p == '0' ) {
    p++;
  }
  for ( power = 0.0; isdigit( *p ); p++ ) {
    power = power * 10 + ( *p - '0' );
  }
  power = pow( 10.0, power );

  if ( sign == '-' ) {
    val /= power;
  } else {
    val *= power;
  }
  return val;
}
