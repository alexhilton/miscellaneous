/*
 * varg.c
 * a program to demonstrate the usage of argument variantion,
 * in standard argument.
 */
#include <stdio.h>
#include <stdarg.h>

float average( int a, ... );

int main( void ) {
  int a = 3, b = 5, c = 6, d = 8;
  float ave = 0.0;
  ave = average( 4, a, b, c, d );
  printf( "the average is: %g\n", ave );
  return 0;
}

float average( int a, ... ) {
  float sum = 0.0;
  int i;
  va_list var_arg;
  va_start( var_arg, a );
  for ( i = 0; i < a; i++ ) {
    sum += va_arg( var_arg, int );
  }
  va_end( var_arg );
  return sum;
}
