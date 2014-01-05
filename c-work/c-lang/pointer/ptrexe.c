/*
 * ptrexe.c
 * pointer exercises.
 */
#include <stdio.h>
#include <stdlib.h>

int fact( int a );

int main( void ) {
  int a;
  int *ptra, *aptra;
  int **ptrptra;
  a = 5;
  ptra = &a;
  ptrptra = &ptra;
  aptra = &a;
  printf( " %d %d %d \n", a, *ptra, **ptrptra );
  printf( " %x %x", ( unsigned long ) ptra, ( unsigned long ) *ptrptra );
  *ptra = fact( 5 );
  printf( " %x\n", ptra );
  printf( " sizeof( long long ) is %d\n", sizeof( long long ) );
  printf( " sizeof( long long int ) is %d\n", sizeof( long long int ) );
  printf( " sizeof( long double ) is %d\n", 
		  sizeof( long double ) );
  return 0;
}

int fact( int a ) {
  if ( a < 2 ) {
    return 1;
  } else {
    return a * fact( a - 1 );
  }
}
