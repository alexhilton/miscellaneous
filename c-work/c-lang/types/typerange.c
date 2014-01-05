/*
 * this file explodes the ranges of types in C, gcc, ANSI, ISO, C89 and 
 * C99.
 */
#include <stdio.h>
#include <limits.h>
#include <float.h>

int main( void ) {
  FILE *out;
  out = fopen( "limits.dat", "a" );
  fprintf( out, "the integer types:\n" );
  fprintf( out, "width of char type in bits is %d\n", CHAR_BIT );
  fprintf( out, "min value of signed char is %d\n", SCHAR_MIN );
  fprintf( out, "max value of signed char is %d\n", SCHAR_MAX );
  fprintf( out, "max value of unsigned char is %d\n", UCHAR_MAX );
  fprintf( out, "min value of unsigned char is 0\n" );
  fprintf( out, "min value of short int is %hd\n", SHRT_MIN );
  fprintf( out, "max value of short int is %hd\n", SHRT_MAX );
  fprintf( out, "max value of unsigned short is %hd\n", USHRT_MAX );
  fprintf( out, "min value of unsigned short is 0\n" );
  fprintf( out, "min value of int is %d\n", INT_MIN );
  fprintf( out, "max value of int is %d\n", INT_MAX );
  fprintf( out, "max value of unsigned int is %u\n", UINT_MAX );
  fprintf( out, "min value of unsigned int is 0\n" );
  fprintf( out, "min value of long is %ld\n", LONG_MIN );
  fprintf( out, "max value of long is %ld\n", LONG_MAX );
  fprintf( out, "max value of unsigned long is %lu\n", ULONG_MAX );
  fprintf( out, "min value of unsigned long is 0\n" );
  fprintf( out, "min value of long long is %lld\n", LLONG_MAX );
  fprintf( out, "max value of long long is %lld\n", LLONG_MAX );
  fprintf( out, "max value of unsigned long long is %llu\n", ULLONG_MAX );
  fprintf( out, "min value of unsigned long long is 0\n" );

  fprintf( out, "Floating-point types:\n" );
  fprintf( out, "min value of float is %g\n", FLT_MIN );
  fprintf( out, "max value of float is %g\n", FLT_MAX );
  fprintf( out, "min value of double is %g\n", DBL_MIN );
  fprintf( out, "max value of double is %g\n", DBL_MAX );
  fprintf( out, "min value of long double is %Le\n", LDBL_MIN );
  fprintf( out, "max value of long double is %Le\n", LDBL_MAX );
  fprintf( out, "\n\n=========================================================\n\n" );

  return 0;
}
