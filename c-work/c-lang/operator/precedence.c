/*
 * precedence.c
 * a program to demonstrate operator precedence.
 */
#include <stdio.h>

int *foo( const int size );

int main( int argc, char **argv ) {
  int a, b = 1, c = 2;
  a = b = c;
  printf( "a = %d, b = %d, c = %d\n", a, b, c );
  a = b+++c;/* equavilent to a = b++ + c */
  printf( "a = b+++c is %d\n", a );
  printf( "while a, b and c are %d %d %d\n", a, b, c );
  a = b+++++c;/*an error*/
  printf( "a = b+++c is %d\n", a );
  printf( "while a, b and c are %d %d %d\n", a, b, c );
  const int size = 10;
  int *arr;
  arr = foo( size );

  return 0;
}

int *foo( const int size ) {
	int a[ 10 ];
	return a;
}
